//////////////////////////////// display binary tree ///////////////////////////////

#ifndef MAP_DISPLAY_HPP
# define MAP_DISPLAY_HPP 1

// You can change those define

# define __NODE		node	 // name of your strucure/class which contain your node
# define __VALUE	value	 // name of your value variable in your structure/class
# define __SIZE		5		 // size between nodes (only for display)
# define __ROOT		root	 // name of your tree's root variable
# define __IS_BLACK	is_black // name of the bool variable for the color of nodes
# define __NIL		nil		 // name of your NULL pointer
# define __RIGHT	right	 // name of the right child of your nodes
# define __LEFT		left	 // name of the left child of your nodes

///////////////////////////////////////////////////////////////////////////////////

# define __BLACK "\033[40m"
# define __RED   "\e[1;41m"
# define __STOP  "\033[0m"

private:

int count_from_node(__NODE *ptr, int count = 0) {
	if (ptr != __NIL) {
		if (ptr->__RIGHT != __NIL)
			count += count_from_node(ptr->__RIGHT);
		if (ptr->__LEFT != __NIL)
			count += count_from_node(ptr->__LEFT);
		return (++count);
	}
	return count;
}

int count_btw_p(__NODE *ptr, bool is_right) {
	if (is_right) {
		return count_from_node(ptr->__LEFT);
	}
	else {
		return count_from_node(ptr->__RIGHT);
	}
}

std::vector<std::vector <int> > aff;

bool search_v(int level) {
	for (size_t i = 0; i < aff.size(); i++) {
		if (aff[i][0] == level) {
			aff[i][1]--;
			if (aff[i][1] <= 0)
				aff.erase(aff.begin() + i);
			return (true);
		}
	}
	return (false);
}

void aff_chars(std::string a, std::string b, int size = -1) {
	size = (size == -1) ? a.size() : size;
	std::cout << a;
	for (int i = __SIZE; i - size > 0; i--)
				std::cout << b;
}

public:

void print_tree(__NODE *ptr, int level = 0, bool is_right = 0)
{
	int i;
	if (ptr != __NIL)
	{
		print_tree(ptr->__RIGHT, level + 1, 1);
		std::cout << std::endl;
		for (i = 1; i < level && ptr != __ROOT; i++) {
			if (search_v(i))
				aff_chars("│", " ", 1);
			else
				aff_chars(" ", " ");
		}
		if (ptr != __ROOT) {
			if (is_right && count_btw_p(ptr, is_right) > 0) {
				std::vector<int> tmp;
				tmp.push_back(level);
				tmp.push_back(count_btw_p(ptr, is_right));
				aff.push_back(tmp);
			}
			if (is_right)
					aff_chars("╭", "─", 1);
			else
					aff_chars("╰", "─", 1);
		}
		if (ptr->__LEFT != __NIL && count_btw_p(ptr->__LEFT, 0) > 0) {
			std::vector<int> tmp;
			tmp.push_back(level + 1);
			tmp.push_back(count_btw_p(ptr->__LEFT, 0));
			aff.push_back(tmp);
		}
		if (ptr->__IS_BLACK)
			std::cout << __BLACK << ptr->__VALUE << __STOP;
		else
			std::cout  << __RED << ptr->__VALUE << __STOP;
		print_tree(ptr->__LEFT, level + 1, 0);
	}
}

#endif /* MAP_DISPLAY_HPP */