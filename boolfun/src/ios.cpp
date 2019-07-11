std::string trim_left (std::string s)
{
    if (s == "") return s;
    std::string result = "";
    int i;
    for (i=0; s[i]==' '; ++i);
    for (i=i; i<s.length(); ++i)
        result += s[i];
    return result;
}

std::string trim_right (std::string s)
{
    if (s == "") return s;
    std::string result = "";
    int j;
    for (j=s.length()-1; s[j-1]==' '; --j);
    for (int i=0; i<j; ++i)
        result += s[i];
    return result;
}

std::string trim (std::string s)
{
    return trim_left(trim_right(s));
}

std::string lower_case (std::string s) {
	std::string result = "";
	
}
