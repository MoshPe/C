void replaceCh(char* buff)
{
	int temp;
	if (*buff == 0||*(buff+1)==0)
		return;
		temp = *(buff+1);
		* (buff+1) = *buff;
		*buff = temp;
		replaceCh(buff + 1);
}