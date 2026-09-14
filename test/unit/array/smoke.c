	Array array = {0};
	array_init(&array, sizeof(int));

	int x = 67, y = 99, z = 1054;
	array_push_back(&array, &x);
	array_push_back(&array, &y);
	array_push_back(&array, &z);

	printf("yay! n = %d", *(int*)array_at_clamped(&array, 999));

	array_free(&array);