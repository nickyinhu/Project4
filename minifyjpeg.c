#include "minifyjpeg.h"
#include "magickminify.h"
#include <stdio.h>
#include <rpc/rpc.h>

/* Implement the needed server-side functions here */

bool_t
minify_proc_1_svc(input var, output *result, struct svc_req *rqstp){

	void *src = var.arg.arg_val;
	ssize_t src_len = var.arg.arg_len;
	bool_t retval;

    printf("%s\n", "1");

    printf("Input file size is: %d\n", var.arg.arg_len);

	magickminify_init();

    printf("%s\n", "2");

	result->output_u.res.res_val = magickminify(src,src_len,(ssize_t*)var.size);

	result->output_u.res.res_len = (u_int)*var.size;

    printf("Result file size is %d\n", result->output_u.res.res_len);
    printf("Actual Result file size is %d\n", *var.size);

    printf("%s\n", "3");
    return retval;

}

int
minify_prog_1_freeresult (SVCXPRT *svc_xprt, xdrproc_t xdr_proc, caddr_t xdr_caddr){
	magickminify_cleanup();
	(void) xdr_free(xdr_proc,xdr_caddr);
	return 1;
}