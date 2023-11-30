import os

if __name__ == "__main__":
    print("Running Test Cases\n")
    test_dir = "./test-cases/"
    output_dir = "./test-cases/tac/"
    parser = "./translator"
    test_files = [f for f in os.listdir(test_dir) if f.endswith(".nc")]
    print("Starting Parser\n")
    # make command
    os.system("make build")
    for test_file in test_files:
        print("Running test case: " + test_file)
        os.system(parser + "<" + test_dir + test_file + " > " + output_dir + test_file + ".tac")
        print("Done\n")
    print("Cleaning up\n")
    os.system("make clean")
    print("Done\n")