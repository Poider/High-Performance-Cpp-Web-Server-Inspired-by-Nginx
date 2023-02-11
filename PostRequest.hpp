/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:37:58 by klaarous          #+#    #+#             */
/*   Updated: 2023/02/11 18:44:00 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_REQUEST_HPP
#define POST_REQUEST_HPP

#include "A_Request.hpp"
#include "filesystem.hpp"
#include "static/ContentTypes.hpp"
#include <cstring>

class PostRequest : public  A_Request
{
	FileSystem fs;
	int received;
	bool file_initialized;
	int body_length;
	public :
		PostRequest()
		{
			std::vector < std::string > content_type_vector = _headers.at("Content-Length");
			std::string content_len = content_type_vector[0];
			body_length = std::stoi(content_len);
			received = 0;
			file_initialized = false;
		}
		
		void handleRequest(std::string &body, Client &client)
		{
			//open file where to 
			std::vector < std::string > content_type_vector = _headers.at("Content-Type");
			std::string content_type = content_type_vector[0];
			if(!file_initialized)
			{
				fs = FileSystem(_path/*get best match*/, WRITE, ContentTypes::getExtention(content_type));
				fs.open();
				file_initialized = true;
			}

			/*
				if chunked then clean it first then forward to the next
				check if chunk size is in midde of the request (in case he sends two chuncks and you recv 1 and a half)
				if chunk size is 0 meaning its done then  close and flag up its done with body
			*/

			if(content_type == "multipart/form-data")
			{
				// take care content-type or content_disposition with their boundaries having boundary set somewhere

				//fs.close(); then make a new file when theres a new one
			}
			else
			{
				received += body.size();
				fs.Write(body);
			}
	
			if(body_length >= received)
			{
				fs.close();
				//flag up body is done to either close connection or reset the whole request
			}
		};

		void handle_length_upload(std::string &body, Client &client)
		{

		}

		void handle_chunked_upload(std::string &body, Client &client)
		{

		}

		~PostRequest()
		{

		}
	
};


#endif

