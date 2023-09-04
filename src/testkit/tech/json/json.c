#include <stdio.h>
#include <json-c/json.h>

int main()
{
	json_object* myobj;
	json_object* dataobj;

	myobj = json_object_new_object();
	dataobj = json_object_new_object();

	json_object_object_add(dataobj, "test1", json_object_new_int(1));
	json_object_object_add(dataobj, "test2", json_object_new_string("TEST2"));
	json_object_object_add(myobj, "testData", dataobj);

	printf("myobj.to_string()=%s\n", json_object_to_json_string(myobj));

	json_object_put(myobj);
	json_object_put(dataobj);

	return 0;
}
