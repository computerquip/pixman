int main () {
    /* Most modern architectures have a NOP instruction, so this is a fairly generic test. */
	asm volatile ( "\tnop\n" : : : "cc", "memory" );
    return 0;
}