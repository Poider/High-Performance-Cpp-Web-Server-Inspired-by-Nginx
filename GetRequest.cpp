/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetRequest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:42:18 by klaarous          #+#    #+#             */
/*   Updated: 2023/02/12 16:14:16 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GetRequest.hpp"
#include "client.hpp"

void GetRequest::handleRequest(std::string &body, Client &client, bool& body_done)
{
	if (!body.empty())
	{
		client.set_error_code(BAD_REQUEST);
	}
	body_done = true;
}

GetRequest::~GetRequest()
{

}