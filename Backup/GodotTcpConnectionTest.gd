extends Control


var _timer = 0
var _count = 0
var _stream = null


# Called when the node enters the scene tree for the first time.
func _ready():
	_stream = StreamPeerTCP.new()
	_stream.set_no_delay(true)
	print("Connection attempt: ", _stream.connect_to_host("127.0.0.1", 8001))
	# I also tried _stream.set_no_delay(true) here instead of above.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	_stream.poll()
	
	var status = _stream.get_status()
	if status != StreamPeerTCP.STATUS_CONNECTED:
		print("Socket not connected yet. Status is: ", status)
		return;

	_stream.put_data([8, 1, 2, 3, 4, 5, 6, 7, _count])

	if _stream.get_available_bytes():
		var response = _stream.get_data(_stream.get_available_bytes())
		print("Received: ", response)
