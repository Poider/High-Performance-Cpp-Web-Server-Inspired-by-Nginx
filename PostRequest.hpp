/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:37:58 by klaarous          #+#    #+#             */
/*   Updated: 2023/02/12 18:14:23 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_REQUEST_HPP
#define POST_REQUEST_HPP

#include "A_Request.hpp"
#include "filesystem.hpp"
#include "client.hpp"
#include "static/ContentTypes.hpp"
#include <cstring>

class PostRequest : public  A_Request
{
	FileSystem fs;
	int received;
	bool file_initialized;
	int body_length;
	bool is_chunked;
	public :
		PostRequest();
		
		
		void post_init();
		

		void handleRequest(std::string &body, size_t size, Client &client);
		


		~PostRequest();
};


#endif

