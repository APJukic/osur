/*!  Dynamic memory allocator - first fit */

#include <kernel/kprint.h>
#define _FF_SIMPLE_C_
#include <lib/ff_simple.h>
#ifndef ASSERT
#include ASSERT_H
#endif

/*!
 * Initialize dynamic memory manager
 * \param mem_segm Memory pool start address
 * \param size Memory pool size
 * \return memory pool descriptor
*/
void *ffs_init(void *mem_segm, size_t size)
{

	size_t start, end;
	ffs_hdr_t *chunk, *border;
	ffs_mpool_t *mpool;

	ASSERT(mem_segm && size > sizeof(ffs_hdr_t) * 2);

	/* align all on 'size_t' (if already not aligned) */
	start = (size_t) mem_segm;
	end = start + size;
	ALIGN_FW(start);
	mpool = (void *) start;		/* place mm descriptor here */
	start += sizeof(ffs_mpool_t);
	ALIGN(end);

	mpool->first = NULL;

	if (end - start < 2 * HEADER_SIZE)
		return NULL;

	border = (ffs_hdr_t *) start;
	border->size = sizeof(size_t);
	MARK_USED(border);

	chunk = GET_AFTER(border);
	chunk->size = end - start - 2 * sizeof(size_t);
	MARK_FREE(chunk);
	CLONE_SIZE_TO_TAIL(chunk);

	border = GET_AFTER(chunk);
	border->size = sizeof(size_t);
	MARK_USED(border);

	ffs_insert_chunk(mpool, chunk); /* first and only free chunk */

	return mpool;
}

/*!
 * Get free chunk with required size(or slightly bigger)
 * \param mpool Memory pool to be used(if NULL default pool is used)
 * \param size Requested chunk size
 * \return Block address, NULL if can't find adequate free chunk
 */
void *ffs_alloc(ffs_mpool_t *mpool, size_t size)
{

	ffs_hdr_t *iter, *chunk,*after,*before;

	ASSERT(mpool);

	size += sizeof(size_t) * 2; /* add header and tail size */
	if (size < HEADER_SIZE)
		size = HEADER_SIZE;

	/* align request size to higher 'size_t' boundary */
	ALIGN_FW(size);
	kprintf("Free chunks before malloc:\n");
	iter = mpool->first;
	int i=0;
	while (iter != NULL){
		kprintf("chunk: %d, size: \t-[%d]\n",i,iter->size);
		iter = iter->next;
		i++;
	}
	iter = mpool->first;
	while (iter != NULL && iter->size < size)
		iter = iter->next;

	if (iter == NULL){
		kprintf("No adequate free chunk found, time to merge neighbors\n");
	chunk=mpool->first;
		before = ((void *) chunk) - sizeof(size_t);
	while(1){
		if (CHECK_FREE(before))
		{
			before = GET_HDR(before);
			ffs_remove_chunk(mpool, before);
			before->size += chunk->size; /* join */
			chunk = before;
		}	
		/* join with right? */
		after = chunk->next;
		if(chunk->next==NULL){
			kprintf("No enough memory!!\n");
			return NULL;
		}

		if (chunk->next!=NULL)
		{

		ffs_remove_chunk(mpool, after);
		
		chunk->size += after->size; /* join */
		if(chunk->next!=NULL)
		chunk->next=after->next;

		}
		if (chunk->size >= size)
			break;
		}
		kprintf("After merging chunks are:\n");
			iter = mpool->first;
	i=0;
	while (iter != NULL){
		kprintf("chunk: %d, size: \t-[%d]\n",i,iter->size);
		iter = iter->next;
		i++;

	};

	}

	iter = mpool->first;
	while (iter != NULL && iter->size < size)
		iter = iter->next;

	if (iter->size >= size + HEADER_SIZE)
	{
		/* split chunk */
		/* first part remains in free list, just update size */
		iter->size -= size;
		CLONE_SIZE_TO_TAIL(iter);

		chunk = GET_AFTER(iter);
		chunk->size = size;
	}
	else { /* give whole chunk */
		chunk = iter;

		/* remove it from free list */
		ffs_remove_chunk(mpool, chunk);
	}

	MARK_USED(chunk);
	CLONE_SIZE_TO_TAIL(chunk);

	kprintf("Free chunks after malloc:\n");
	iter = mpool->first;
	i=0;
	while (iter != NULL){
		kprintf("chunk: %d, size: \t-[%d]\n",i,iter->size);
		iter = iter->next;
		i++;
	};

	return ((void *) chunk) + sizeof(size_t);
}

/*!
 * Free memory chunk
 * \param mpool Memory pool to be used(if NULL default pool is used)
 * \param chunk Chunk location(starting address)
 * \return 0 if successful, -1 otherwise
 */
int ffs_free(ffs_mpool_t *mpool, void *chunk_to_be_freed)
{
ffs_hdr_t *iter;
		kprintf("Free chunks before free:\n");
	iter = mpool->first;
	int i=0;
	while (iter != NULL){
		kprintf("chunk: %d, size: \t-[%d]\n",i,iter->size);
		iter = iter->next;
		i++;
	};
	ffs_hdr_t *chunk;

	ASSERT(mpool && chunk_to_be_freed);

	chunk = chunk_to_be_freed - sizeof(size_t);
	ASSERT(CHECK_USED(chunk));

	MARK_FREE(chunk); /* mark it as free */


	/* insert chunk in free list */
	ffs_insert_chunk(mpool, chunk);

	/* set chunk tail */
	CLONE_SIZE_TO_TAIL(chunk);
kprintf("Free chunks after free:\n");
	iter = mpool->first;
	i=0;
	while (iter != NULL){
		kprintf("chunk: %d, size: \t-[%d]\n",i,iter->size);
		iter = iter->next;
		i++;
	};
	kprintf("\n\n\n");

	return 0;
}

/*!
 * Routine that removes an chunk from 'free' list(free_list)
 * \param mpool Memory pool to be used
 * \param chunk Chunk header
 */
static void ffs_remove_chunk(ffs_mpool_t *mpool, ffs_hdr_t *chunk)
{

	if (chunk == mpool->first) /* first in list? */
		mpool->first = chunk->next;
	else
		chunk->prev->next = chunk->next;

	if (chunk->next != NULL)
		chunk->next->prev = chunk->prev;
}

/*!
 * Routine that insert chunk into 'free' list(free_list)
 * \param mpool Memory pool to be used
 * \param chunk Chunk header
 */
static void ffs_insert_chunk(ffs_mpool_t *mpool, ffs_hdr_t *chunk)
{
	chunk->next = mpool->first;
	chunk->prev = NULL;

	if (mpool->first)
		mpool->first->prev = chunk;

	mpool->first = chunk;
}
