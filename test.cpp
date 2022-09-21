#include <iostream>
#include <string>
#include "colored_text.h"
using namespace std;
int main () {
    ctext::text("This text is yellow\n", ct::YELLOW);
    ctext::text("&aThis &1text &bis &cformatted &dwith &6diffe&erent &fcolors\n");
    ctext::bgtext("This text is green on dark red background\n", ct::DARK_RED, ct::GREEN);
    ctext::bgtext("&19This &2atext &3bis &4cformatted &5dwith &6ediffe&87rent &0fcolors &f0and &0fbackgrounds\n");
    ctext::rainbow_cycle("This text is a cycling rainbow\n");
    ctext::rainbow_bg_cycle("This text is a cycling rainbow with colored background\n");
    ctext::rainbow("This text is one rainbow\n");
    ctext::rainbow_bg("This text is one rainbow with colored background\n");
    cin.ignore();
    cin.get();
    return 0;
}