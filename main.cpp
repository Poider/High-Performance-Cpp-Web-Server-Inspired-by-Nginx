/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:34:04 by klaarous          #+#    #+#             */
/*   Updated: 2023/02/07 18:57:51 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "webserv.hpp"


std::string readFile(std::string file)
{
	std::ifstream myfile (file);

	std::string fileContents;
	
	std::string serverConfigs = "";
	if ( myfile.is_open() ) 
	{

		std::string sa;
        while (getline(myfile, sa))
		
            fileContents += sa + "\n";
        myfile.close();
	}
	return (fileContents);
};




int main(int ac , char **av)
{

	if (ac != 2)
	{
		std::cerr << "number argument Not valid !" << std::endl;
		return (0);
	}
	std::ifstream myfile (av[1]);
	ConfigParser parser = ConfigParser(readFile(av[1]));

	std::map<std::string, ServerMap > servers;
	SOCKET maxSocketSoFar = -1;
	fd_set reads , writes, readyReads, readyWrites;

	FD_ZERO(&reads), FD_ZERO(&writes), FD_ZERO(&readyWrites), FD_ZERO(&readyReads);
	servers = parser.parseServerConfig();
	if(!CreateHostSockets(servers, maxSocketSoFar, reads, writes))
		return (0);

	while (1)
	{
		try
		{
			readyReads = reads;
			readyWrites = writes;
			if (select(maxSocketSoFar + 1, &readyReads, &readyWrites, 0, 0) < 0) {
				fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
				break;
			}
			for (auto &xs : servers)
			{
				for (auto &ser : xs.second)
				{
					Server &server  = ser.second;
					ListClients &clients = server.getClients();
					ft::Http http(reads, writes, clients,server);
					if (FD_ISSET(server.getSocket(), &readyReads))
						server.addClient(maxSocketSoFar, reads, writes);
					for (int i = 0; i < clients.getNumberClient(); i++)
					{
						int sizeClient = clients.getNumberClient();
						if (FD_ISSET(clients[i].socket, &readyReads))
							http.getRequest(i);
						if (i >= 0  && FD_ISSET(clients[i].socket, &readyWrites) && clients[i].path)
							http.sendResponse(i);
					}	
				}
			}
		}
		catch (std::exception &e)
		{
			std::cout << "error happend " <<  e.what() << std::endl;
			break;
		}
	}
	closeHosts(servers);
    return 0;
}