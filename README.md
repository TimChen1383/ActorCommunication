# ActorCommunication

Communicating between controller and door actor using cast and delegate. When the controller actor has been overlapped, the controller will light up and send a signal to door actor. After door actor receive the signal, the door will run the open animation.

To make it works you have to do followings :
- Place both ActorCommunication actor and MagicDoor actor in the level

1. For ActorCommunication actor 
- Choose a MagicDoor actor in the details panel to communicate with

2. For MagicDoor actor
- Set up door mesh in mesh component slot. This will the mesh that actor is going to move
- Set up “DoorOffsetValue” in detail panel to decide the distance length of door movement
- Create a curve float and add to the “TimeCure” slot. The actor will use the value stored in curve float as movement value


 
![Communicate](https://github.com/TimChen1383/ActorCommunication_UE/assets/37008451/8d013836-57b4-4f12-8d18-ceb23415484e)
