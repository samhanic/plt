#include "../server.h"
#include <iostream>
using namespace std;
using namespace server;

void ServicesManager::registerService (unique_ptr<AbstractService> service) {
    services.push_back(std::move(service));
}

AbstractService* ServicesManager::findService (const string& url) const {
    for (auto& service : services) {
        const string& pattern(service->getPattern());
		
        if (url.find(pattern) != 0)
			
            continue;
        if (url.size() > pattern.size() && url[pattern.size()] != '/')
			
            continue;
        return service.get();
    }
    return nullptr;
}

HttpStatus ServicesManager::queryService (string& out, const string& in, const string& url, const string& method) { 
    AbstractService* service = findService(url);
    if (!service)
        throw ServiceException(HttpStatus::NOT_FOUND,"Service "+url+" not found");

    // Look for a potential id (ex: /my/service/<id>)
    const string& pattern(service->getPattern());
    int id = 0;
	
    if (url.size() > pattern.size()) {
        string end = url.substr(pattern.size());
        if (end[0] != '/')
            throw ServiceException(HttpStatus::BAD_REQUEST,"Incorrect URL (expected: <service>/<number>)");
        end = end.substr(1);
        if (end.empty())
            throw ServiceException(HttpStatus::BAD_REQUEST,"Incorrect URL (expected: <service>/<number>)");
        try {
            size_t pos = 0;
            id = stoi(end,&pos);
            if (pos != end.size())
                throw ServiceException(HttpStatus::BAD_REQUEST,"Incorrect URL : '"+end+"' is not a number");
        }
        catch(...) {
            throw ServiceException(HttpStatus::BAD_REQUEST,"Incorrect URL : '"+end+"' is not a number");
        }
    }
    // Different methods
    if (method == "GET") {
		int n_id=0;
		for(size_t i=0; i<services.size(); i++){
			if(!services[i]->isVersion()){
				PlayerService& player_service=static_cast<PlayerService&>(*services[i]);
				n_id=player_service.getGame().getIDseq();
			}
		}
		if(id<n_id){
        	cerr << "GET request " << pattern << " with id=" << id << endl;
		}
        Json::Value jsonOut;
        HttpStatus status = service->get(jsonOut,id);
        out = jsonOut.toStyledString();
        return status;
    }
    else if (method == "POST" && in[2]!='r' && in[0]=='{') {
        cerr << "POST request " << pattern << " with data: " << in << endl;
        Json::Reader jsonReader;
        Json::Value jsonIn;
        if (!jsonReader.parse(in,jsonIn))
            throw ServiceException(HttpStatus::BAD_REQUEST,"Invalid data: "+jsonReader.getFormattedErrorMessages());
        return service->post(jsonIn,id);
    }
    else if ((method == "POST" && in[2]=='r'&& in[0]=='{')) {
		
		Json::Reader jsonReader;
        Json::Value jsonIn;
        if (!jsonReader.parse(in,jsonIn)){
            throw ServiceException(HttpStatus::BAD_REQUEST,"Invalid data: "+jsonReader.getFormattedErrorMessages());
			cerr << "PUT request " << pattern << " with data:" << in << endl;
		}
        cerr << "PUT request " << pattern << " with data: {\"name\":" << jsonIn["name"].asString()<<" ,\"free\":"<<jsonIn["free"]<<"}" << endl;
        
        Json::Value jsonOut;
        HttpStatus status = service->put(jsonOut,jsonIn);
        out = jsonOut.toStyledString();
        return status;
    }
	else if (method=="PUT"){
		
        cerr << "PUT request " << pattern << " with data: " << in << endl;
        Json::Reader jsonReader;
        Json::Value jsonIn;
        if (!jsonReader.parse(in,jsonIn))
            throw ServiceException(HttpStatus::BAD_REQUEST,"Invalid data: "+jsonReader.getFormattedErrorMessages());
        Json::Value jsonOut;
        HttpStatus status = service->put(jsonOut,jsonIn);
        out = jsonOut.toStyledString();
        return status;
	}
	
    else if (method=="DELETE" || (method == "POST" && in[0]=='D')) {
        cerr << "DELETE request" << endl;
        return service->remove(id);
    }
    throw ServiceException(HttpStatus::BAD_REQUEST,"Invalid "+method+" method");
}