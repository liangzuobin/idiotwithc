#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include "sha256/sha256.h"
#include "uuid/uuid.h"

void sign_demo()
{
	const char expect[] = "75947738A61E77D768A914761C1C692B3F660A1B52706420D87695CE4AB06E39";
	const unsigned char to_sign[] = "nonce=abcedfg&param1=value1&param2=value2&timestamp=12345678higklmn";
	unsigned char buf[32];
	// char ch[1024] = {0};
	char *ch = (char *)malloc(256 * sizeof(char));
	sha256_hash(buf, to_sign, strlen((char *)to_sign));
	// printf("sha256 = ");
	int i;
	for (i = 0; i < 32; i++)
	{
		sprintf(&ch[strlen(ch)], "%02X", buf[i]);
		// printf("%s", ch);
	}
	printf("ex = %s\n", expect);
	printf("ch = %s\n", ch);
	printf("equals %d\n", strcmp((char *)expect, (char *)ch));
	free(ch);
}

void uuid_demo()
{
	char buf[37];
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

void test_rand()
{
	printf("time %ld \n", time(NULL));
	int i;
	for (i = 0; i < 3; i++)
	{
		uuid_demo();
	}
}

int main(void)
{
	// mv from deps uuid, cause this should be exec only once.
	// 从 deps 的 uuid.c 里边挪出来，这句放在 main 函数里执行一次就行了。
	srand(time(NULL));

	while (1)
	{
		// 监听程序...
		// 坚挺到有刷卡，执行...
		uuid_demo();

		sign_demo();

		request_demo();

		test_rand();
		usleep(2000 * 1000); // 2 seconds
	}

	return 0;
}