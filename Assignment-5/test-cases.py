import os

if __name__ == "__main__":
    print("Running Test Cases\n")
    test_dir = "./test-cases/"
    output_dir = "./test-cases/tac/"
    compiler = "./compiler"
    test_files = [f for f in os.listdir(test_dir) if f.endswith(".nc")]
    print("Starting Compiler\n")
    # make command
    os.system("make build")
    for test_file in test_files:
        print("Running test case: " + test_file)
        os.system(compiler + "<" + test_dir + test_file + " > " + output_dir + test_file.split(".")[0] + ".tac")
        print("Done\n")
    print("Cleaning up\n")
    os.system("make clean")
    print("\nDone\n")