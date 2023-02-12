/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:37:58 by klaarous          #+#    #+#             */
/*   Updated: 2023/02/12 16:54:18 by mel-amma         ###   ########.fr       */
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
	bool is_chunked;
	public :
		PostRequest()
		{
			file_initialized = false;
			is_chunked = false;
		};
		
		void post_init()
		{
			auto it = _headers.find("Content-Length");
			if(it != _headers.end())
			{
				std::vector < std::string > content_type_vector = it->second;
				std::string content_len = content_type_vector[0];
				body_length = std::stoi(content_len);
			}
			else
			{
				body_length = 0;
				is_chunked = true;
			}
			received = 0;
			file_initialized = true;
		}

		void handleRequest(std::string &body, Client &client,bool &body_done)
		{
			// std::cout << "handling body"  << body.size()<< std::endl;
			//open file where to 

			auto it = _headers.find("Content-Type");
			if(it == _headers.end())
			{
				//case no body
				body_done= true;
				return ;
			}

			if(!file_initialized)
				post_init();
			
			std::vector < std::string > content_type_vector = _headers.at("Content-Type");
			std::string content_type = content_type_vector[0];
			if(!file_initialized && content_type != "multipart/form-data")
			{
				std::string str("./public/uploads/upload_");
				//upload_store check if its there, check upload pass or just put in default upload path
				fs = FileSystem(str/*get best match*/, WRITE, ContentTypes::getExtention(content_type));
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
				//fs.Write(body);
			}
			
				// std::cout << body.size() << " "<<  received << " " << body_length << std::endl;
			if(body_length <= received)
			{
				std::cout << "finished" << std::endl;
				fs.close();
				//flag up body is done to either close connection or reset the whole request
				body_done = true;
			}
		};


		~PostRequest()
		{

		}
	
};


#endif

