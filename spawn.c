#include <stdio.h>
#include "controller.h"

int main(int argc, char *argv[])
{
  Controller* ctl = newController("echo \"hello world\"", NULL, "spawning");
  return spawn(ctl);
}
