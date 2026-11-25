void test()
{
	struct Array arr = {0};
	array_init(&arr);

	array_push_back(&arr, 5);
	array_push_back(&arr, 10);
	array_push_back(&arr, 15);
	array_push_back(&arr, 20);
	array_push_back(&arr, 25);
	array_push_back(&arr, 30);
	array_push_back(&arr, 35);
	array_push_back(&arr, 40);
	array_push_back(&arr, 45);
	array_push_back(&arr, 50);

	FOR_EACH (int *, i, &arr) {
		*i += 5;
	}

	FOR_EACH_CONST (int *, i, &arr) {
		printf("number %d\n", *i);
	}

	array_free(&arr);
}