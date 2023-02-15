/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundaryHandler.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:48:13 by mel-amma          #+#    #+#             */
/*   Updated: 2023/02/15 18:23:35 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BOUNDRY_HANDLER__
#define BOUNDRY_HANDLER__

#define EXTRA_BOUNDARY
#include <map>
#include <cstring>
#include <iostream>
#include <utility>
#include "filesystem.hpp"


//test substr size andd test join with past null string

struct BoundaryHandler{

FileSystem 	*fs;
std::string extra;
size_t extra_len;//boundry max is 70
bool initialized;
std::string boundary;

//map of what to (write+size) + (content-type)OrEmpty to add on last file opened
typedef std::map<std::pair<std::string, size_t>, std::string> BoundaryRetType;

BoundaryHandler();
BoundaryRetType clean_body(std::string &body, size_t size);
void set_boundary(std::string& boundary, FileSystem *fs);
bool is_initialized();
bool clean_boundary(std::string &str, size_t &size, BoundaryRetType &res);//clean body from boundary
std::string parse_mini_header(std::string &body, size_t size);
void fill_extra(std::string &str, size_t size);//split string, saves extra, returns what to be written

~BoundaryHandler();

    
};


#endif