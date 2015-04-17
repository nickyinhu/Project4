struct input {
  opaque arg<>;
  int *size;
};

struct output {
  opaque res<>;
};

program MINIFY_PROG { /* RPC service name */
  version MINIFY_VERS {
    output MINIFY_PROC(input) = 1; /* proc1 */
  } = 1; /* version1 */
} = 0x31230000; /* service id */
