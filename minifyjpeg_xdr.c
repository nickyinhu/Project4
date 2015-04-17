/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "minifyjpeg.h"

bool_t
xdr_input (XDR *xdrs, input *objp)
{
	register int32_t *buf;

	 if (!xdr_bytes (xdrs, (char **)&objp->arg.arg_val, (u_int *) &objp->arg.arg_len, ~0))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->size))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_output (XDR *xdrs, output *objp)
{
	register int32_t *buf;

	 if (!xdr_bytes (xdrs, (char **)&objp->res.res_val, (u_int *) &objp->res.res_len, ~0))
		 return FALSE;
	return TRUE;
}
