#ifndef OUTPUT_H
#define OUTPUT_H

//score is directly passed form main
//password is directly passed form main
//errorcode is only present if the -f flag is used
void tojson(int score,const char *password,int errorcode);
void toxml(int score,const char *password,int errorcode);

#endif
