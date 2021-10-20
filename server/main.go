package main

import (
	"bufio"
	"encoding/binary"
	"fmt"
	"io"
	"net"
	"os"
	"sync"
	"sync/atomic"

	flatbuffers "github.com/google/flatbuffers/go"
	msg "github.com/jeb2239/pong/Pong/Net/State"
)

const MIN = 1
const MAX = 100

type ClientManager struct {
	clientMap *sync.Map
	listener  net.Listener
	currIdx   uint64
}

func NewClientManager(nl net.Listener) *ClientManager {
	return &ClientManager{
		clientMap: &sync.Map{},
		listener:  nl,
		currIdx:   0,
	}
}

func (cm *ClientManager) Accept() {
	c, err := cm.listener.Accept()
	if err != nil {
		return
	}
	idxToUse := atomic.LoadUint64(&cm.currIdx)
	cm.clientMap.Store(idxToUse, &c)
	atomic.AddUint64(&cm.currIdx, 1)
	go cm.HandleConnection(c)

}

func (cm *ClientManager) HandleConnection(c net.Conn) {
	
	
	fmt.Printf("Serving %s\n at Id: %d\n", c.RemoteAddr().String())

	for {
		buffer := make([]byte, 2048)
		_, err := bufio.NewReader(c).Read(buffer)
		messageType := msg.GetSizePrefixedRootAsMessage(buffer, 0)
		destId := messageType.SendTo()
		val, ok := cm.clientMap.Load(&destId)
		if !ok {
			
		}
		oppCon:=val.(net.Conn)
		
		unionTable := new(flatbuffers.Table)

		if messageType.Type(unionTable) {
			unionType := messageType.TypeType()
			switch unionType {
			case msg.PacketTypeLogin:
				fmt.Println("Login")
				playerLogin := new(msg.PlayerLogin)
				playerLogin.Init(unionTable.Bytes, unionTable.Pos)
			case msg.PacketTypeLoginAck:
				fmt.Println("LoginAck")
			case msg.PacketTypeReplicationData:
				gameData := new(msg.Game)
				gameData.Init(unionTable.Bytes, unionTable.Pos)

			}
		}

		if err != nil {
			fmt.Println(err)
			return
		}

		//c.Write([]byte(string(netData)))
	}

}

func main() {
	arguments := os.Args
	if len(arguments) == 1 {
		fmt.Println("Please provide a port number!")
		return
	}

	PORT := ":" + arguments[1]
	l, err := net.Listen("tcp4", PORT)
	if err != nil {
		fmt.Println(err)
		return
	}
	defer l.Close()
	cm := NewClientManager(l)
	for {

		cm.Accept()

	}
}
