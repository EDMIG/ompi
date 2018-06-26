/*
 * Copyright (c) 2018      DataDirect Networks. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

#include "ime_native.h"

#include "ompi_config.h"
#include "fs_ime.h"

#include "mpi.h"
#include "ompi/constants.h"
#include "ompi/mca/fs/fs.h"

/*
 *	file_close_ime
 *
 *	Function:	- closes a new file
 *	Accepts:	- file handle
 *	Returns:	- Success if file closed
 */
int mca_fs_ime_file_close (ompio_file_t *fh)
{
    int ret;

    fh->f_comm->c_coll->coll_barrier (fh->f_comm,
                                     fh->f_comm->c_coll->coll_barrier_module);
    /* reset errno */
    errno = 0;

    ret = ime_native_close(fh->fd);
    if (ret != 0) {
        return mca_fs_ime_get_mpi_err(errno);
    }

    return OMPI_SUCCESS;
}
