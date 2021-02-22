import inlinecpp
mymodule = inlinecpp.createLibrary(
name="cpp_string_library",
includes="#include UImain.cpp",
include_dirs=["D:/Google_Drive/Oriol/Formation/Epitech/Tek4/AI/Files/ai_problem_solving_epitech/BackEnd/Public",
    "D:/Google_Drive/Oriol/Formation/Epitech/Tek4/AI/Files/ai_problem_solving_epitech/BackEnd/Private",
    "D:/Google_Drive/Oriol/Formation/Epitech/Tek4/AI/Files/ai_problem_solving_epitech",
    "D:/Google_Drive/Oriol/Formation/Epitech/Tek4/AI/Files/ai_problem_solving_epitech/UI"],
function_sources=[
"""bool matchesPattern(const char *str, const char *pattern)
{
    //GetProblem();
    return false;
}
"""])


def my_function():
  print("Hedddeeeelelofffff from a function")
  string = "one"
  for pattern in "o*", "x*", "^o*":
      print repr(string), "matches", repr(pattern), ":",
      print mymodule.matchesPattern(string, pattern)
