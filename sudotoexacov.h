#ifndef SUDOTOEXACOV_H
#define SUDOTOEXACOV_H

class element
{
public:
	int position;
	int number;

	friend std::ostream &operator<<(std::ostream &ostream, const element &ele);
};

int addrow(const int position, const int num, const int linkrow, std::vector<nonZeroPosition> &vec, std::vector<element> &index);
int convert(int matric[], std::vector<nonZeroPosition> &exa, std::vector<element> &index);

#endif