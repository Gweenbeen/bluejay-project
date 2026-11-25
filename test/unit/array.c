struct Name
{
	const char *name;
	uint16_t age;
};

struct NameArray
{
	DEFINE_ARRAY_HEADER(struct Name);
};
DEFINE_ARRAY_IMPL(struct NameArray, name_array, struct Name);

int main(int argc, const char *argv[])
{
	struct NameArray arr = {0};
	name_array_init(&arr);

	name_array_push_back(&arr, (struct Name){ "Justin", 18 });
	name_array_push_back(&arr, (struct Name){ "ajkldklasdjlakd", 30 });

	for (size_t i = 0; i < 99; i++) {
		name_array_push_back(&arr, (struct Name){ "hello", 10 });
	}

	ARRAY_FOR_EACH_CONST (struct Name *, i, arr) {
		printf("my name is %s and my age is %hu\n", i->name, i->age);
	}

	name_array_free(&arr);
}

struct IntArray
{
	DEFINE_ARRAY_HEADER(int);
};
DEFINE_ARRAY_IMPL(struct IntArray, int_array, int);

int main(int argc, const char *argv[])
{

	struct IntArray arr = {0};

	int_array_init(&arr);

	int_array_push_back(&arr, 50);
	
	for (size_t i = 0; i < 14; i++) {
		int_array_push_back(&arr, i + 10);
	}

	ARRAY_FOR_EACH_CONST (int *, i, arr) {
		printf("nubmah = %d\n", *i);
	}

	int_array_free(&arr);

	printf("Hello, world!\n");

	return 0;
}