#include <SFML/Network.hpp>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <microhttpd.h>
#include <cstring>
#include "server.h"


using namespace sf;
using namespace std;
using namespace server;

class Request {
public:
    struct MHD_PostProcessor *pp = nullptr;
    string data;
    ~Request() {
        if (pp) MHD_destroy_post_processor (pp);
    }
};

// Destroy the data of a request
static void
request_completed (void *cls, struct MHD_Connection *connection,
                   void **con_cls, enum MHD_RequestTerminationCode toe)
{
  Request *request = (Request*)*con_cls;
  if (request) {
      delete request;
      *con_cls = nullptr;
  }
}

// Main handler
static int
main_handler (void *cls,      
          struct MHD_Connection *connection,
          const char *url, 
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr) 
{
    // Data for a request (in multiple calls of this function)
    Request *request = (Request*)*ptr;

    // First call for this request
    if (!request) { 
        request = new Request();
        if (!request) {
            return MHD_NO;
        }
        *ptr = request;

        return MHD_YES;
    }    
    
    // Case where we retrieve data sent by the user
    if (strcmp(method, MHD_HTTP_METHOD_POST) == 0
     || strcmp(method, MHD_HTTP_METHOD_PUT) == 0) {
        if (*upload_data_size != 0) {
            request->data = upload_data;
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
    catch(ServiceException& e) {
        status = e.status();
        response = e.what();
        response += "\n";
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

int main(int argc, char* argv[])
{
    if(argc>1){
        if(strcmp(argv[1],"listen")==0){
            cout << "Server is running" << endl;
            try {
                ServicesManager servicesManager;
                Game game;
                unique_ptr<PlayerService> ptrPlayerService(new PlayerService(ref(game)));  
                servicesManager.registerService(move(ptrPlayerService));

                struct MHD_Daemon *d;
                d = MHD_start_daemon(
                        MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
                        8080,
                        NULL, NULL, 
                        &main_handler, (void*) &servicesManager,
                        MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
                        MHD_OPTION_END);
                if (d == NULL)
                    return 1;
                cout << "Press enter to exit" << endl;
                    (void) getc(stdin);
                    MHD_stop_daemon(d);
                }
            catch(exception& e) {
                cerr << "Exception: " << e.what() << endl;
            }
        }
    }
    return 0;
}


