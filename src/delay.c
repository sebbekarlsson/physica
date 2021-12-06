#include <physica/delay.h>
#include <date/date.h>
#include <stdio.h>

void ph_delay(float d) {
  Date start = date_now();

  while (1) {
    Date now = date_now();

    Date diff = date_diff(&now, &start);

    double delta = diff.milliseconds_static * 1000;
    if (delta >= d) return;
  }
}
