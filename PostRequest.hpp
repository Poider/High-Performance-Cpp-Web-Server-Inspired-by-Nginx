/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:37:58 by klaarous          #+#    #+#             */
/*   Updated: 2023/02/21 16:16:57 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_REQUEST_HPP
#define POST_REQUEST_HPP

#include "A_Request.hpp"
#include "filesystem.hpp"
#include "client.hpp"
#include "static/ContentTypes.hpp"
#include "ChunckContentHandler.hpp"
#include "BoundaryHandler.hpp"
#include <cstring>

class PostRequest : public  A_Request
{
	FileSystem 	fs;
	int 		received;
	bool 		file_initialized;
	int 		body_length;
	bool 		is_chunked;
	ChunkContentHandler chunk_handler;
	BoundaryHandler boundary_handler;

	public :
		PostRequest();
		
		
		bool post_init();
		

		void handleRequest(std::string &body, size_t size, Client &client);
		
		void setBodyAsFinished(Client &client);
		void open_file(std::string& contentType);

		void write_body(std::string& body, size_t size);
		void write_body(std::vector<const char *>  &chunks, size_t size);
		bool handle_boundary(std::string &body, size_t size, Client &client);

		~PostRequest();
};


#endif
