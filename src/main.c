#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "sha256/sha256.h"
#include "uuid/uuid.h"

void sign_demo()
{
	const char expect[] = "75947738A61E77D768A914761C1C692B3F660A1B52706420D87695CE4AB06E39";
	const unsigned char to_sign[] = "nonce=abcedfg&param1=value1&param2=value2&timestamp=12345678higklmn";
	unsigned char buf[32];
	char *ch;
	sha256_hash(buf, to_sign, strlen((char *)to_sign));
	printf("sha256 = ");
	int i;
	for (i = 0; i < 32; i++)
	{
		sprintf(ch, "%X", buf[i]);
		printf("%s", ch);
	}
	printf("\n");
	printf("equals %d\n", strcmp((char *)expect, (char *)buf));
}

void uuid_demo()
{
    const char buf[37];
    random_uuid(buf);
    printf("uuid = %s\n", buf);
}

void request_demo()
{
	CURL *curl;
	if ((curl = curl_easy_init()))
	{
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_URL, "http://api.beta.meican.com/v2.1/libra/fixedpricepay");

#ifdef SKIP_PEER_VERIFICATION
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Cache-Control: no-cache");
		headers = curl_slist_append(headers, "content-type: application/x-www-form-urlencoded; charset=utf-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "param1=value1&param2=value2");

		CURLcode ret = curl_easy_perform(curl);
		if (ret != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));

		curl_easy_cleanup(curl);
	}
}

int main(void)
{
	char a[] = "hello";
	char b[] = "world";
	char buf[20];
	strcpy(buf, "");
	strcat(buf, a);
	strcat(buf, " ");
	strcat(buf, b);
	printf("%s\n", buf);

	uuid_demo();

	sign_demo();

	request_demo();

	return 0;
}