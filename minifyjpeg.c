#include "minifyjpeg.h"
#include "magickminify.h"
#include <stdio.h>
#include <rpc/rpc.h>

/* Implement the needed server-side functions here */

bool_t
minify_proc_1_svc(var, result, req)
				input var;
				output *result;
				struct svc_req *req;
{
	printf("%s\n", "1");
	magickminify_init();
	printf("%s\n", "2");
	void *src;
	printf("%s\n", "3");
	src = malloc(sizeof(void*));
	printf("%s\n", "4");
	memcpy(src, var.arg.arg_val, sizeof(var.arg.arg_val));
	printf("%s\n", "5");
	ssize_t src_len = (ssize_t) var.arg.arg_len;
	ssize_t *dst_len = (ssize_t*) var.size;
	printf("%s\n", "6");
	void *dst_val = magickminify(src,src_len,dst_len);

	result->res.res_val = dst_val;

	// magickminify_cleanup();

	return result;
}

int
minify_prog_1_freeresult (SVCXPRT *svc_xprt, xdrproc_t xdr_proc, caddr_t xdr_caddr){
	magickminify_cleanup();
	(void) xdr_free(xdr_proc,xdr_caddr);
	return 0;
}