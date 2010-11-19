#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int
main (int argc, char ** argv)
{
  std::ifstream input ("converted.txt");
  std::string filename;
  std::vector<std::string> filenames;
  std::vector<bool> depths;
  std::vector<std::pair<std::string, std::string> > pairs;
  while (input >> filename)
  {
    filenames.push_back (filename);
    depths.push_back (filename.find ('.') == std::string::npos);
  }
  input.close();

  for (int i = 0; i < filenames.size() - 1; ++i)
  {
    if (depths[i] != depths[i + 1])
    {
      std::string depth = depths[i] ? filenames[i] : filenames[ i + 1];
      std::string rgb = depths [i] ? filenames[i + 1]: filenames[i];
      pairs.push_back(make_pair(rgb, depth));
      ++i;
    }
  }

  for (int i = 0; i < pairs.size(); ++i)
  {
    std::stringstream ss1;
    ss1 << "converted/" << pairs[i].first;
    std::stringstream ss1_new;
    ss1_new << "images/" << i << ".jpg";
    std::ifstream inputRGB (ss1.str().c_str());
    std::ofstream outputRGB (ss1_new.str().c_str());
    outputRGB << inputRGB.rdbuf();
    outputRGB.close();
    inputRGB.close();

    std::stringstream ss2;
    ss2 << "converted/" << pairs[i].second;
    std::stringstream ss2_new;
    ss2_new << "images/" << i;
    std::ifstream inputDepth (ss2.str().c_str());
    std::ofstream outputDepth (ss2_new.str().c_str());
    outputDepth << inputDepth.rdbuf();
    outputDepth.close();
    inputDepth.close();
  }

  return 0;
}
