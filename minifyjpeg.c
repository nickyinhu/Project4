#include "minifyjpeg.h"
#include "magickminify.h"
#include <stdio.h>
#include <rpc/rpc.h>

/* Implement the needed server-side functions here */

output *
minify_proc_1_svc(input var, struct svc_req *rqstp){
	static output result;

	void *src = var.arg.arg_val;	
	ssize_t src_len = var.arg.arg_len;

	magickminify_init();

	result.res.res_val = magickminify(src,src_len,(ssize_t*)var.size);
	result.res.res_len = (u_int)*var.size;

	return &result;
}

int
minify_prog_1_freeresult (SVCXPRT *svc_xprt, xdrproc_t xdr_proc, caddr_t xdr_caddr){
	magickminify_cleanup();
	(void) xdr_free(xdr_proc,xdr_caddr);
	return 0;
}