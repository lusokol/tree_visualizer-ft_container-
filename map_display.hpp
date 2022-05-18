//////////////////////////////// display binary tree ///////////////////////////////

// You can change those define

#define __NODE node // name of your strucure/class which contain your node
#define __VALUE value // name of your value variable in your structure/class
#define __SIZE 10 // size between nodes (only for display)

///////////////////////////////////////////////////////////////////////////////////

#if __SIZE < 8
	#define __DISPLAY 8
#else
	#define __DISPLAY __SIZE
#endif

private:

int count_from_node(__NODE *ptr, int count = 0) {
	if (ptr) {
	if (ptr->right)
		count += count_from_node(ptr->right);
	if (ptr->left)
		count += count_from_node(ptr->left);
	return (++count);
	}
	return count;
}

int count_btw_p(__NODE *ptr) {
	if (ptr->parent->right == ptr) {
		return count_from_node(ptr->left);		
	}
	else {
		return count_from_node(ptr->right);		
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
	for (int i = __DISPLAY; i - size > 0; i--)
				std::cout << b;
}

public:

void aff_tree(__NODE *ptr, int level = 0, bool is_right = 0)
{
	int i;
	if (ptr != NULL)
	{
		aff_tree(ptr->right, level + 1, 1);
		std::cout << std::endl;
		for (i = 1; i < level && ptr != root; i++) {
			if (search_v(i))
				aff_chars("│", " ", 1);
			else
				aff_chars(" ", " ");
		}
		if (ptr != root) {
			if (is_right && count_btw_p(ptr) > 0) {
				std::vector<int> tmp;
				tmp.push_back(level);
				tmp.push_back(count_btw_p(ptr));
				aff.push_back(tmp);
			}
			if (is_right)
					aff_chars("╭", "─", 1);
			else
					aff_chars("╰", "─", 1);
		}
		if (ptr->left && count_btw_p(ptr->left) > 0) {
			std::vector<int> tmp;
			tmp.push_back(level + 1);
			tmp.push_back(count_btw_p(ptr->left));
			aff.push_back(tmp);
		}
		std::cout << ptr->__VALUE;
		aff_tree(ptr->left, level + 1, 0);
	}
}