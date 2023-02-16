/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BoundaryHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:44:45 by mel-amma          #+#    #+#             */
/*   Updated: 2023/02/16 18:43:57 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BoundaryHandler.hpp"


size_t BoundaryHandler::findSubstring(const std::string& str, const std::string& substr)
{
    const char* strData = str.data();
    const char* substrData = substr.data();
    size_t strLength = str.length();
    size_t substrLength = substr.length();

    for (size_t i = 0; i <= strLength - substrLength; i++)
    {
        if (memcmp(strData + i, substrData, substrLength) == 0)
            return i;
    }

    return std::string::npos;
}

BoundaryHandler::BoundaryHandler()
{
    stage = NEED_CONTENT_TYPE;
    initialized = false;
    done = false;
};

//map of what to (write+size) + (content-type)OrEmpty to add on last file opened


//if returned map size is 0 then just go again till next iteration
//change map to vector
BoundaryHandler::BoundaryRetType BoundaryHandler::clean_body(std::string &body, size_t size)
{
    BoundaryRetType res;
    std::string before_boundary;
    if(clean_boundary(body,size,before_boundary))
        stage = NEED_CONTENT_TYPE;
    //clean_body again after clearing boundary/map it returns join with the current map
    
    std::string contentType;
    
    //if boundary found//
    std::string contentType = parse_mini_header(body,size);//returns new contentType -> set it in the map
    if(contentType.empty())
    {
        //return the previous stuff than boundary, and save whats after it
    }
    /*if couldnt, wait next time and return only before boundary 
    and flag waiting new contentType so next time we return a contentType to open file
    save the after boundary in the buffer extra
    else normally(no boundary -> no miniheader) save last 100 and send whats before that
    if we go in and we find NeedContentType, no need to clean boundary,
    skip to miniheader after the joins*/
    
    
    return res;
};

//return true if boundry found
bool BoundaryHandler::clean_boundary(std::string &body, size_t &size, std::string &before_boundary)
{
    size_t pos = find_boundary_start(body);
    if(pos == std::string::npos || pos + boundary.size() + 2 > body.size())//(so boundary ends with \r\n or --)
        return 0;
    //clean body from boundary// store whats before boundary
    before_boundary = body.substr(0,pos);
    size_t after_boundary_pos;
    after_boundary_pos = find_boundary_end(body,pos);
    if(after_boundary_pos == std::string::npos)
    {
        //put error and make it not do shit even recursively if error
        done = true;
        return 0;
    }
    if(!done)
    {
        body = body.substr(after_boundary_pos, size);
        size = body.size();
        // put it in the vector?
    }
    return 1;
}

size_t BoundaryHandler::find_boundary_end(std::string &body,size_t start)
{
    size_t cursor = start;
    const char *strData = body.data();
    size_t strLength = body.size();
    
    for (size_t i = 0; i <= strLength - 2; i++)
    {
        if(memcmp(strData + cursor, "\r\n", 2) == 0)
            return i;
        if(memcmp(strData + cursor, "--", 2) == 0)
        {
            done = true;
            return i;
        }
    }
    return std::string::npos;//meaning boundary was syntax failure
}


std::string BoundaryHandler::parse_mini_header(std::string &body, size_t size)
{//send body after boundary
    //do I parse also contentDisposition//if so return pair of string and map of keyvalue
    std::string contentType = get_content_type(body,size);
    if(contentType.empty())
    {
        stage = NEED_CONTENT_TYPE;
        return(std::string());
    }
    //if I find contentType
    //update body to point to after(start of body)
    stage = IN_BODY;
    return contentType;
}

void BoundaryHandler::join_up_receives(std::string &body)
{
    body = extra + body;
    extra.clear();
};


std::string BoundaryHandler::get_content_type(std::string &body, size_t size)
{
    size_t pos = findSubstring(body, "Content-Type");
    size_t type_value = pos + 12 + 1 + 1; //content-type len + : + space
                            
    //try to cut typevalue to \r\n if not possible return -
    //  - cant find contentType now, till next() // empty string
    
};

void BoundaryHandler::fill_extra(std::string &str, size_t pos)
{
    //split string, saves extra, changes str to what to be written
    extra = str.substr(pos,str.size());
};

void BoundaryHandler::set_boundary(std::string& boundary, FileSystem *fs)
{
    this->boundary = "--"+boundary;
    this->fs = fs;
};

size_t BoundaryHandler::find_boundary_start(std::string &body)
{
    size_t pos = findSubstring(body, boundary);
    return pos;
}


bool BoundaryHandler::is_done()
{
    return done;
};


bool BoundaryHandler::is_initialized()
{
    return initialized;
}
BoundaryHandler::~BoundaryHandler()
{

};
