#include "Tuples.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Canvas
{
	int width = 50;
	int height = 50;
	vector<vector<Color>> canvas;

public:

	Canvas() {
		Create();

	}

	Canvas(int width, int height) {
		this->width = width;
		this->height = height;
		Create();
	}

	void Create() {
		for (int x = 0; x < width; x++) {
			vector<Color> temp;
			for (int y = 0; y < height; y++) {
				temp.push_back(Color(0, 0, 1));
			}
			canvas.push_back(temp);
		}
	}

	void Fill(Color color) {
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				canvas[x][y] = color;
			}
		}
	}

	void setPixel(int x, int y, Color color) {
		if (x < width && y < height) {
			canvas[x][y] = color;
		}
	}

	Color getPixel(int x, int y) {

		Color temp = Color();

		if (x < width && y < height) {
			temp = canvas[x][y];
		}
		return temp;
	}

	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}

	enum FileType {
		PPM
	};

	void Save(string fileName) {

		FileType type = PPM;

		switch (type) {
		case PPM:
			savePPM(fileName);
			break;
		default:
			break;
		}
	}

	void savePPM(string fileName) {

		//plain format PPM cannot have a line linger than 70 characters
		int maxVal = 255;
		string header = "P3\n" +
			to_string(getWidth()) + " " + to_string(getHeight()) + "\n" +
			to_string(maxVal) + "\n";
		string body = "";
		int count = 0;
		int maxChar = 70;



		for (int x = 0; x < getWidth(); x++) {
			for (int y = 0; y < getHeight(); y++) {

				Color color = getPixel(x, y);
				int red = (int)(color.x * 255);
				int green = (int)(color.y * 255);
				int blue = (int)(color.z * 255);

				if (red > 255) {
					red = 255;
				}
				if (green > 255) {
					green = 255;
				}
				if (blue > 255) {
					blue = 255;
				}
				string r = to_string(red);
				string g = to_string(green);
				string b = to_string(blue);

				body += r + " " + g + " " + b + " ";
				count += r.length() + g.length() + b.length() + 3;

				if (count >= maxChar - 13) { //13 is the max number of characters for a color pixel
					body += "\n";
					count = 0;
				}
			}
		}

		string footer = "\n";
		string total = header + body + footer;
		fileName += ".ppm";
		ofstream outfile(fileName);
		outfile << total;
		outfile.close();
	}

	double clamp(double x, double min, double max) {
		if (x < min) {
			return min;
		}
		if (x > max) {
			return max;
		}
		return x;
	}

};