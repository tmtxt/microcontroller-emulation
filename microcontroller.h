namespace microcontroller {
    class Microcontroller
	{
	private:
		// program counter: internal CPU register that point to the memory
		// location that contains the next instruction
		int programCounter;

		// microcontroller's memory, dynamically allocated
		unsigned char* memory;
		
	public:
		// reset the controller
		void reset();

		// execute the instruction coorecsponding to the opcode
		void execute(int opcode)

		// constructor
		Microcontroller();

		// destructor
		virtual ~Microcontroller();
	};
}
