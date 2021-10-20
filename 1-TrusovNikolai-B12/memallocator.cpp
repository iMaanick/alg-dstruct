#ifdef __cplusplus
extern "C" {
#endif

#include"memallocator.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
	typedef struct descriptor {
		int size;
		struct descriptor* next;
	}descriptor;

	typedef struct {
		descriptor* desc;
	}memAllocator;

	memAllocator Allocator = { (descriptor*)NULL };
	int memgetminimumsize() {
		return sizeof(descriptor);
	}

	int memgetblocksize() {
		return sizeof(descriptor);
	}

	int meminit(void* InitMem, int size) {
		if (!InitMem || size <= memgetminimumsize())
			return 0;
		descriptor desc;
		Allocator.desc = (descriptor*)InitMem;
		Allocator.desc->size = -(size - memgetminimumsize());
		Allocator.desc->next = NULL;
		return 1;
	}

	void* memalloc(int size) {
		if (size <= 0 || !Allocator.desc)
			return NULL;
		void* PtrToReturn = NULL;
		int FoundCounter = 0;
		int sizebefore;
		descriptor* cur = Allocator.desc;
		descriptor* required = NULL;
		descriptor* addnext = NULL;
		descriptor* firstfit = NULL;
		while (cur) {
			if (cur->size < 0 && abs(cur->size) >= size) {
				if (FoundCounter == 0) {
					FoundCounter++;
					firstfit = cur;
				}
				else if (FoundCounter == 1) {
					FoundCounter++;
					break;
				}
			}
			required = cur;
			cur = cur->next;
		}
		if (FoundCounter) {
			if (FoundCounter == 1)
				required = firstfit;
			else
				required = cur;
			sizebefore = -(required->size);
			PtrToReturn = (void*)(required + 1);
			required->size = size;
			if (sizebefore - size > memgetblocksize()) {
				addnext = (descriptor*)((char*)PtrToReturn + size);
				addnext->next = required->next;
				addnext->size = -(sizebefore - size - memgetblocksize());
				required->next = addnext;
			}
			else {
				required->size = sizebefore;
			}
			return PtrToReturn;
		}
		else
			return NULL;
	}

	void memfree(void* memory) {
		int block = memgetblocksize();
		descriptor* cur = Allocator.desc;
		descriptor* prev = NULL;
		descriptor* next = NULL;
		while (cur) {
			if ((char*)memory - (char*)(cur + 1) > 0) {
				prev = cur;
				cur = cur->next;
			}
			else if ((char*)(cur + 1) == (char*)memory)
				break;
			else return;
		}
		if (!cur || cur->size < 0)
			return;
		cur->size = -cur->size;
		if (prev && prev->size < 0) {
			prev->size = -(abs(prev->size) + block + abs(cur->size));
			prev->next = cur->next;
		}
		next = cur->next;
		if (next && next->size < 0) {
			if (prev && prev->size < 0)
				cur = prev;
			cur->size = -(abs(cur->size) + block + abs(next->size));
			cur->next = next->next;
		}
	}
	void memdone() {
		descriptor* desc = Allocator.desc;
		while (desc) {
			if (desc->size > 0) {
				fprintf(stderr, "Memory leak detected: %d bytes of %p\n", desc->size, desc);
			}
			desc = desc->next;
		}
	}
#ifdef __cplusplus
}
#endif 