/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetRequest.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:37:58 by klaarous          #+#    #+#             */
/*   Updated: 2023/02/12 16:14:20 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_REQUEST_HPP
#define GET_REQUEST_HPP

#include "A_Request.hpp"

class GetRequest : public  A_Request
{
	public :
		void handleRequest(std::string &body, Client &client, bool& body_done);
		~GetRequest();
};


#endif

