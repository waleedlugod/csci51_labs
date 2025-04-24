A pair of programs that uses local IPC to copy a text file.

Producer: <textfile> <shared memory size in bytes>
Copies the contents of the text file provided to a shared memory in chunks based on the input size.
Size of shared memory should be the same as the consumer.

Consumer: <textfile> <shared memory size in bytes>
Writes the contents of the shared memory in the text file in chunks based on the input size.
Size of shared memory should be the same as the producer.