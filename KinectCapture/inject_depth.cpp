#include <cstdlib>
#include <string>
#include <sstream>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>

int
main (int argc, char ** argv)
{
  if (argc != 3)
  {
    return -1;
  }
  std::vector<uint16_t> depths;
  std::ifstream inputSift (argv[1]);
  std::ifstream inputDepth (argv[2]);

  depths.reserve (640*480);
  uint16_t depth;
  while (inputDepth >> depth)
  {
    depths.push_back (depth);
  }
  assert (depths.size() == 640*480);
  inputDepth.close();

  std::vector<std::string> lines;
  std::string firstLine;
  getline(inputSift, firstLine);
  int keypoints = atoi (firstLine.c_str());
  lines.push_back (firstLine);
  std::cerr << keypoints << std::endl;
  for (int i = 0; i < keypoints; ++i)
  {
    std::string line;
    getline (inputSift, line);
    std::stringstream ss;
    ss << line;
    std::vector<std::string> tokens;
    std::string token;
    while (ss >> token)
    {
      tokens.push_back (token);
    }
    std::stringstream ss_new;
    for (int i = 0; i < 2; ++i)
    {
      ss_new << tokens[i] << " ";
    }
    float x = atof (tokens[1].c_str());
    float y = atof (tokens[0].c_str());
    ss_new << depths [ y * 640 + x] << " ";
    for (int i = 2; i < tokens.size(); ++i)
    {
      ss_new << tokens [i] << " ";
    }
    lines.push_back (ss_new.str());
    for (int i = 0; i < 7; ++i)
    {
      getline (inputSift, line);
      lines.push_back (line);
    }
  }
  inputSift.close();
  std::ofstream output (argv[1]);
  for (int i = 0; i < lines.size(); ++i)
  {
    output << lines[i] << std::endl;
  }
  output.close();
  return 0;
}
