/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BoundaryHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:44:45 by mel-amma          #+#    #+#             */
/*   Updated: 2023/02/15 18:36:27 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BoundaryHandler.hpp"

BoundaryHandler::BoundaryHandler()
{
    initialized = false;
};

//map of what to (write+size) + (content-type)OrEmpty to add on last file opened

BoundaryHandler::BoundaryRetType BoundaryHandler::clean_body(std::string &body, size_t size)
{
    BoundaryRetType res;
    clean_boundary(body,size);
    //clean_body again after clearing boundary/map it returns join with the current map
    //send back the first beside last 100
    parse_mini_header(body,size);//returns new contentType -> set it in the map
    
    
    
    //if map size is 0 then just go again till next iteration
    return res;
};

//return true if boundry found
bool BoundaryHandler::clean_boundary(std::string &body, size_t &size, std::string &before_boundary)
{
    //if boundry_found
    //clean body from boundary// store whats before boundary
    //before_boundary str(body.datagit )
    //body.data() = body.data() + boundary_end_pos
}

std::string BoundaryHandler::parse_mini_header(std::string &body, size_t size)
{
    std::string contentType;
    //do I parse also contentDisposition//if so return pair of string and map of keyvalue

    return contentType;
}

void BoundaryHandler::fill_extra(std::string &str, size_t size)
{
    //split string, saves extra, changes str to what to be written
}

void BoundaryHandler::set_boundary(std::string& boundary, FileSystem *fs)
{
    this->boundary = "--"+boundary;
    this->fs = fs;
};

bool BoundaryHandler::is_initialized()
{
    return initialized;
}
BoundaryHandler::~BoundaryHandler()
{

};
