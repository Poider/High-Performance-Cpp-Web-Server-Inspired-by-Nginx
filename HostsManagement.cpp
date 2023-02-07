/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HostsManagement.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:44:42 by mel-amma          #+#    #+#             */
/*   Updated: 2023/02/07 18:44:45 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "server.hpp"
#include "parsing/configParser/ConfigParser.hpp"
#include "StatusCode.hpp"
#include "_http.hpp"

void closeHosts(std::map<std::string, ServerMap > &servers)
{
	for (auto xs : servers)
	{
		for (auto ser : xs.second)
		{
			if (!ISVALIDSOCKET(ser.second.getSocket()))
				ser.second.closeHost();
		}
	}
}


bool CreateHostSockets(std::map<std::string, ServerMap >& servers, SOCKET &maxSocketSoFar, fd_set& reads, fd_set& writes)
{
	for (auto &xs : servers)
	{
		try
		{
			ServerMap::iterator it = xs.second.begin();
			it->second.createSocket();
			SOCKET serverSocket = it->second.getSocket();
			FD_SET(serverSocket, &reads);
			FD_SET(serverSocket, &writes);
			maxSocketSoFar = std::max(maxSocketSoFar, serverSocket);
			it++;
			for (; it != xs.second.end(); it++)
				it->second.setSocket(serverSocket);
		}
		catch (const std::exception &e)
		{
			closeHosts(servers);
			return (0);
		}
	}
	return 1;
}