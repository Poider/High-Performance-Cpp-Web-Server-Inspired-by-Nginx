#ifndef HTTP__HPP
#define HTTP__HPP

#include "includes.hpp"
#include "StatusCode.hpp"
#include "server.hpp"
#include "parsing/configParser/ConfigParser.hpp"
#include "StatusCode.hpp"

namespace ft{


struct Http{
    fd_set& reads;
    fd_set& writes;
    ListClients& clients;
    Server& server;
    Http(fd_set& reads, fd_set& writes, ListClients& clients, Server& server) : reads(reads),\
            writes(writes), clients(clients), server(server)
    {};

    void getRequest(int Client_Number)
    {
        int sz = recv(clients[Client_Number].socket, clients[Client_Number].request, BUFFER_SIZE, 0);
        if (sz < 1)
        {
            printf("Unexpected disconnect from %d.\n",
                   clients[Client_Number].socket);
            clients.dropClient(Client_Number, reads, writes);
        }
        else
        {
            clients[Client_Number].received += sz;
            clients[Client_Number].request[clients[Client_Number].received] = '\0';
            char *request = strstr(clients[Client_Number].request, "\r\n\r\n");
            if (request)// if request is done
                get_request_done(request, Client_Number);
        };
    };

    void sendResponse(int Client_Number)
    {
        if (clients[Client_Number].fp == nullptr)
            server.sendHeaderResponse(clients[Client_Number], reads, writes, Client_Number);
        server.serve_resource(clients[Client_Number]);
        if (clients[Client_Number].fp == nullptr)
            clients.dropClient(Client_Number, reads, writes);
    };

    private :

        void set_bad_request(int Client_Number)
        {
            clients[Client_Number].responseCode = BAD_REQUEST;
            clients[Client_Number].sendError = true;
        }

        void get_request_done(char *request, int Client_Number)
        {
            *request = 0;
            if (strncmp("GET /", clients[Client_Number].request, 5))
                set_bad_request(Client_Number);
            else
            {
                char *path = clients[Client_Number].request + 4;
                char *end_path = strstr(path, " ");
                if (!end_path)
                    set_bad_request(Client_Number);
                else
                {
                    *end_path = 0;
                    clients[Client_Number].path = path;
                }
            }
        }
};

}
#endif 