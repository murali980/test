#include <stdio.h>
#include <stdlib.h>
struct bridge
 {
 int north_waiting;
 int north_crossing;
 int north_consecutive;
 int south_waiting;
 int south_crossing;
 int south_consecutive;
 struct lock *lock;
 struct conditon *northbound_done;
 struct condition *southbound_done;
};
void lock_init(struct bridge *b)
{
 b->north_waiting = 0;
 b->north_crossing = 0;
 b->north_consecutive = 0;
 b->south_waiting = 0;
 b->south_crossing = 0;
 b->south_consecutive = 0;
 lock_init(struct lock *lock);
 cond_init(struct condition *northbound_done);
 cond_init(struct condition *southbound_done);
}
int bridge_arrive_north(struct bridge *b)
{
 lock_acquire(struct lock *lock);
 b->north_waiting++;
 while ((b->south_crossing > 0) || ((b->south_waiting > 0) && (b->north_consecutive >= 5)))
 {
 cond_wait(&b->southbound_done);
 }
 b->north_waiting--;
 b->north_crossing++;
 b->north_consecutive++;
 b->south_consecutive = 0;
 lock_release(struct lock *lock);
}
int bridge_leave_north(struct bridge *b)
{
 lock_acquire(struct lock *lock);
 b->north_crossing--;
 if (b->north_crossing == 0) 
 {
 cond_broadcast(b->northbound_done);
 }
 lock_release(struct lock *lock);
}

int bridge_arrive_south(struct bridge *b)
{
 lock_acquire(struct lock *lock);
 b->south_waiting++;
 while ((b->north_crossing > 0) || ((b->north_waiting > 0) && (b->south_consecutive >= 5)))
{
 cond_wait(&b->northbound_done);
 }
 b->south_waiting--;
 b->south_crossing++;
 b->south_consecutive++;
 b->north_consecutive = 0;
 lock_release(struct lock *lock);
}
int bridge_leave_south(struct bridge *b)
{
 lock_acquire(struct lock *lock);
 b->south_crossing--;
 if (b->south_crossing == 0) 
 {
 cond_broadcast(b->southbound_done);
 }
 lock_release(struct lock *lock);
}
