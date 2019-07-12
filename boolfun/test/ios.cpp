namespace bf {

	std::string trim_left (std::string s) {
		if (s == "") return s;
		std::string result = "";
		int i;
		for (i=0; s[i]==' '; ++i);
		for (i=i; i<s.length(); ++i)
			result += s[i];
		return result;
	}

	std::string trim_right (std::string s) {
		if (s == "") return s;
		std::string result = "";
		int j;
		for (j=s.length()-1; s[j-1]==' '; --j);
		for (int i=0; i<j; ++i)
			result += s[i];
		return result;
	}

	std::string trim (std::string s) {
		return trim_left(trim_right(s));
	}

	void lower_case (std::string &s) {
		for (unsigned int i=0; i<s.length(); i++)
			if ( (s[i] >= 'A') and (s[i] <= 'Z') )
				s[i] = 'a' + (s[i] - 'A');
	}

	int str2int (string s) {
		int x;
		stringstream ss;
		ss.clear();
		ss << s;
		ss >> x;
		return x;
	}
	
	std::string int2str (int x) {
		std::string s;
		stringstream ss;
		ss.clear();
		ss << x;
		ss >> s;
		return s;
	}
	
	std::vector<string> get_words (const std::string s) {
		std::vector<string> result;
		sstringstream ss;
		ss.clear();
		ss << s;
		std::string s1;
		while (ss >> s1)
			result.push_back(s1);
		return result;
	}
	
	std::string trim_all (std::string s) {
	std::string result = "";
	for (int i=0; i<s.length(); i++) {
		if (s[i] == ' ')
			continue;
		result += s[i];
	}
	return result;
} 

}

