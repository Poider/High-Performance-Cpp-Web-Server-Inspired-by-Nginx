/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:49:22 by mel-amma          #+#    #+#             */
/*   Updated: 2023/02/07 18:53:06 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "server.hpp"
#include "parsing/configParser/ConfigParser.hpp"
#include "StatusCode.hpp"
#include "_http.hpp"

void closeHosts(std::map<std::string, ServerMap > &servers);
bool CreateHostSockets(std::map<std::string, ServerMap >& servers, SOCKET &maxSocketSoFar, fd_set& reads, fd_set& writes);

#endif