/***************************************************/
/*     created by TheWebServerTeam 2/14/23         */
/***************************************************/

#ifndef CHUNCKED_
#define CHUNCKED_

# include <iostream>
# include <map>
# include <vector>
# include <set>
# include <string>
# include <fstream>
# include <exception>
# include <stack>
# include <sstream>
# include <algorithm>


class ChunkContentHandler{
private:
	static const unsigned int	maxBuffer = 20;
	unsigned int				expectedContentSize;
	char						nbBuffer[maxBuffer];
	bool						done;

public:

	ChunkContentHandler(){
		done = false;
		expectedContentSize = 0;
		std::memset(nbBuffer, 0, maxBuffer);
	}

	ChunkContentHandler(const ChunkContentHandler& other){
		*this = other;
	}

	ChunkContentHandler& operator=(const ChunkContentHandler& other)
	{
		expectedContentSize = other.expectedContentSize;
		std::memcpy(nbBuffer, other.nbBuffer, maxBuffer);
		return (*this);
	}

	~ChunkContentHandler(){}

public:
	bool is_done()
	{
		return done;
	}
	/**
 	** @brief supply the @param arr with a list of {start_ptr (included) and end_ptr (excluded)} of the chunked content.
	 * @return true if success else false in case of bad hex_number (big than unsigned int or malformed)
 	*/

	bool getHttpChunkContent(const char *chunk, unsigned int chunkSize, std::vector<const char *> &arr){
		int i = 0;

		if (chunkSize == 0) {
			return (true);
		}
		while (nbBuffer[i] != 0)
			i++;
		while (chunkSize--){
			if (expectedContentSize == 0)
			{
				if (arr.size() % 2 == 1)
				{
					arr.push_back(chunk);
				}
				if (i == maxBuffer){
					std::memset(nbBuffer, 0, maxBuffer);
					return (false);
				}
				//std::cout  << "buffer = "  << nbBuffer << " currVal = " << *chunk << std::endl;
				nbBuffer[i] = *chunk;
				if (i >= 1 && !std::strncmp(nbBuffer + (i - 1), "\r\n", 2))
				{
					
					i = 0;
					if (!_setExpectedContentSize())
						return (false);
					//std::cout << "expected  = "  << expectedContentSize << std::endl;
					if (expectedContentSize == 2)
					{
						//std::cout << "done here\n";
						done = true;
						break;
					}
					//std::cout  << "buffer = "  << nbBuffer << std::endl;
					std::memset(nbBuffer, 0, maxBuffer);
				} 
				else
					i++;
			} 
			else 
			{
				if (arr.size() % 2 == 0)
					arr.push_back(chunk);
				expectedContentSize--;
			}
			chunk++;
		}
		if (arr.size() % 2 == 1)
			arr.push_back(chunk);
		return (true);
	}

private:

	bool _setExpectedContentSize(){
		int i = 0;

		while (_isHexChar(nbBuffer[i]))
			i++;
		//std::cout << " i = " << i << std::endl;
		if (nbBuffer[i] != '\r' || nbBuffer[i + 1] != '\n')
		{
			//std::cout << "aaaaa\n";
			return (false);
		}
		nbBuffer[i] = 0;
		try{
			expectedContentSize = std::stoul(nbBuffer, NULL, 16) + 2;
			//std::cout << "nb: " << expectedContentSize << std::endl;
		}catch (std::exception &e){
			//std::cout << "heree\n";
			return (false);
		}
		return (true);
	}


	bool _isHexChar(char c){
		if ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (c >= '0' && c <= '9'))
			return (true);
		return (false);
	}

};

#endif