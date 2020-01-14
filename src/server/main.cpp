#include <iostream>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <cstring>
#include "server/ServicesManager.h"
#include "server/PlayerService.h"

//For debug
#include <string>
#include <iostream>

#define PORT 8080
#define GET 0
#define POST 1
#define ANSWER_LENGTH 1024

using namespace std;
using namespace server;

ServicesManager* manager = new ServicesManager();

class Request {
public:
    struct MHD_PostProcessor *pp = nullptr;
    string data;
    ~Request() {
        if (pp) MHD_destroy_post_processor (pp);
    }
};

static int post_iterator(void *cls,
        enum MHD_ValueKind kind,
        const char *key,
        const char *filename,
        const char *content_type,
        const char *transfer_encoding,
        const char *data, uint64_t off, size_t size) 
{
    return MHD_NO;
}

struct connection_info_struct
{
    int connectiontype;
    char *answerstring;
    struct MHD_PostProcessor *postprocessor;
};

static int
iterate_post (void *coninfo_cls, enum MHD_ValueKind kind, const char *key,
              const char *filename, const char *content_type,
              const char *transfer_encoding, const char *data,
              uint64_t off, size_t size)
{
    struct connection_info_struct *con_info = static_cast<connection_info_struct *>(coninfo_cls);

    if (0 == strcmp (key, "name"))
    {
        if ((size > 0) && (size <= ANSWER_LENGTH))
        {
            char *answerstring;
            answerstring = static_cast<char *>(malloc(ANSWER_LENGTH));
            if (!answerstring) return MHD_NO;

            snprintf (answerstring, ANSWER_LENGTH, "test%s", data);
            con_info->answerstring = answerstring;
        }
        else con_info->answerstring = NULL;

        return MHD_NO;
    }

    return MHD_YES;
}

static void
request_completed (void *cls, struct MHD_Connection *connection,
                   void **con_cls, enum MHD_RequestTerminationCode toe)
{
    struct connection_info_struct *con_info = static_cast<connection_info_struct *>(*con_cls);
    (void)cls;         /* Unused. Silent compiler warning. */
    (void)connection;  /* Unused. Silent compiler warning. */
    (void)toe;         /* Unused. Silent compiler warning. */

    if (NULL == con_info)
        return;

    if (con_info->connectiontype == POST)
    {
        MHD_destroy_post_processor (con_info->postprocessor);
        if (con_info->answerstring)
            free (con_info->answerstring);
    }

    free (con_info);
    *con_cls = NULL;
}


int answer_to_connection (void *cls, struct MHD_Connection *connection,
                          const char *url,
                          const char *method, const char *version,
                          const char *upload_data,
                          size_t *upload_data_size, void **con_cls)
{
    if(NULL == *con_cls) {
        struct connection_info_struct *con_info;

        con_info = static_cast<connection_info_struct *>(malloc(sizeof(struct connection_info_struct)));
        if (NULL == con_info) return MHD_NO;
        con_info->answerstring = NULL;
        if ((0 == strcmp (method, "POST")) or (0 == strcmp (method, "PUT")))
        {
            con_info->postprocessor
                    = MHD_create_post_processor (connection, 1024,
                                                 iterate_post, (void*) con_info);

            if (NULL == con_info->postprocessor)
            {
                free (con_info);
                return MHD_NO;
            }
            con_info->connectiontype = POST;
        }
        else con_info->connectiontype = GET;
        *con_cls = (void*) con_info;
        return MHD_YES;
    }
    if ((0 == strcmp (method, "GET")) or (0 == strcmp (method, "DELETE"))) {
        struct MHD_Response *response;
        int ret;
        std::string out, in;
        HttpStatus code = manager->queryService(out, in, url, method);
        //cout << out.c_str() << endl;
        //cout << "length : " << out.length() << endl;
        response = MHD_create_response_from_buffer(out.length(),
                                                   (void *) out.c_str(), MHD_RESPMEM_MUST_COPY);
        ret = MHD_queue_response(connection, code, response);
        MHD_destroy_response(response);

        return ret;
    }
    if ((0 == strcmp (method, "POST")) or (0 == strcmp (method, "PUT")))
    {
        struct connection_info_struct *con_info = static_cast<struct connection_info_struct *>(*con_cls);
        static HttpStatus code;
        static struct MHD_Response *response;

        if (*upload_data_size != 0)
        {
            MHD_post_process (con_info->postprocessor, upload_data,
                              *upload_data_size);
            *upload_data_size = 0;
            std::string out, in;
            code = manager->queryService(out, upload_data, url, method);
            response = MHD_create_response_from_buffer(out.length(),
                                                       (void *) out.c_str(), MHD_RESPMEM_MUST_COPY);
            //cout << upload_data << endl;
            //cout << "length : " << out.length() << endl;
            return MHD_YES;
        }
        else{
            int ret;
            ret = MHD_queue_response(connection, code, response);
            MHD_destroy_response(response);
            return ret;
        }

    }
    return -1;
}

static int main_handler (void *cls,      
          struct MHD_Connection *connection,
          const char *url, 
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr) 
{
    cout<<"Data reveived"<<endl;
    // Données pour une requête (en plusieurs appels à cette fonction)
    Request *request = (Request*)*ptr;

    // Premier appel pour cette requête
    if (!request) { 
        cout<<"first request"<<endl;
        request = new Request();
        if (!request) {
            return MHD_NO;
        }
        *ptr = request;
        if (strcmp(method, MHD_HTTP_METHOD_POST) == 0
         || strcmp(method, MHD_HTTP_METHOD_PUT) == 0) {
            request->pp = MHD_create_post_processor(connection,1024,&post_iterator,request);
            if (!request->pp) {
                cerr << "Failed to setup post processor for " << url << endl;
                return MHD_NO;
            }
        }
        return MHD_YES;
    }    
    
    // Cas où il faut récupérer les données envoyés par l'utilisateur
    if (strcmp(method, MHD_HTTP_METHOD_POST) == 0
     || strcmp(method, MHD_HTTP_METHOD_PUT) == 0) {
         cout<<"We have data de get : "<<endl;
        MHD_post_process(request->pp,upload_data,*upload_data_size);
        if (*upload_data_size != 0) {
            request->data = upload_data;
            cout<<"DATA is : "<<upload_data<<endl;
            *upload_data_size = 0;
            return MHD_YES;
        }    
    }

    HttpStatus status;
    string response;
    try {

        ServicesManager *manager = (ServicesManager*) cls;
        status = manager->queryService(response,request->data,url,method);
    }
    catch(exception& e) {
        status = HttpStatus::SERVER_ERROR;
        response = e.what();
        response += "\n";
    }
    catch(...) {
        status = HttpStatus::SERVER_ERROR;
        response = "Unknown exception\n";
    }

    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(response.size(),(void *)response.c_str(),MHD_RESPMEM_MUST_COPY);
    if (strcmp(method,MHD_HTTP_METHOD_GET) == 0) {
        MHD_add_response_header(mhd_response,"Content-Type","application/json; charset=utf-8");
    }
    int ret = MHD_queue_response(connection, status, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

//=====================================================================================================
//
//                                              STARTING SERVER
//
//=====================================================================================================

int main(int argc,char* argv[]){

    if(strcmp(argv[1],"hello")==0){
        cout<<"Hello world"<<endl;
		Json::Value root;
		root["tabCmd"];
    }

    if(strcmp(argv[1],"listen")==0){
        try{
            cout<<"Starting server for listening"<<endl;
            Game serverGame = Game();
            ServicesManager servicesManager;

            manager->registerService(unique_ptr<PlayerService>(new PlayerService(serverGame)));

            Game game;
            PlayerService playerService(std::ref(game));
            std::unique_ptr<AbstractService> ptr_playerService (new PlayerService(playerService));

            struct MHD_Daemon *daemon;

            // daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG, PORT, NULL, NULL,
            //                         &answer_to_connection, NULL,
            //                         MHD_OPTION_NOTIFY_COMPLETED, &request_completed, NULL,
            //                         MHD_OPTION_END);
            daemon = MHD_start_daemon(// MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG | MHD_USE_POLL,
				        MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
				        // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG | MHD_USE_POLL,
				        // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
				        8080,
				      	NULL, NULL, 
				        &main_handler, (void*) &servicesManager,
				        MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
				        MHD_OPTION_END);
            if (daemon == NULL) {
                cout<<"Null daemon"<<endl;
                return 1;
            }

            getchar ();

            cout << "Enter to stop server" << endl;
            (void) getc(stdin);
            MHD_stop_daemon (daemon);

            return 0;
        }
        catch(exception& excep){
            cerr << "Exception : "<<excep.what() <<endl;
            return -1;
        }
    } 
}