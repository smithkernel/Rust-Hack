using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using static covet.cc.Memory.Memory;

// It's in testing only. Don't rely on files.

public static void InitializeGlobals()
        {
            new Thread(() =>
            {
                Thread.CurrentThread.IsBackground = true;

                IntPtr i = Memory.Memory.Mem.ReadVirtualMemory<IntPtr>(Rust.Rust.BaseAddress + Rust.Rust.GOMAddress);
                Rust.Rust.i = i;

                IntPtr bn = Memory.Memory.Mem.ReadVirtualMemory<IntPtr>(Rust.Rust.GameAssembly + Rust.Rust.BaseNetworkable);


                UInt64 unk1 = Memory.Memory.Mem.ReadVirtualMemory<UInt64>((IntPtr)bn + 0xb8);

                UInt64 client_entities = Memory.Memory.Mem.ReadVirtualMemory<UInt64>((IntPtr)unk1);

                UInt64 entity_realm = Memory.Memory.Mem.ReadVirtualMemory<UInt64>((IntPtr)client_entities + 0x10);

                UInt64 buffer_list = Memory.Memory.Mem.ReadVirtualMemory<UInt64>((IntPtr)entity_realm + 0x28);


                while (true)
                {
                   

                    #region Misc
                    RECT rect;
                    Memory.Memory.GetWindowRect(handle, out rect);
                   
                    ScreenSize = RectToSize(rect);
                    MidScreen = new Vector2(ScreenSize.Width / 2, ScreenSize.Height / 2);
                    ScreenRect = rect;
                    #endregion


                    List<Rust.Structs.Entity> oldEntityList = new List<Rust.Structs.Entity>();

                    oldEntityList.Clear();


                    UInt64 object_list = Memory.Memory.Mem.ReadVirtualMemory<UInt64>((IntPtr)buffer_list + 0x18);

                    UInt64 object_list_size = Memory.Memory.Mem.ReadVirtualMemory<UInt64>((IntPtr)buffer_list + 0x10);

                    for (UInt64 Object = 0u; Object < object_list_size; Object++)
                    {
                        try
                        {


                            var da = object_list + 0x20 + (Object * 8);

                            UInt64 GameObject = Memory.Memory.Mem.ReadVirtualMemory<UInt64>((IntPtr)da);



                            UInt64 unk3 = Memory.Memory.Mem.ReadVirtualMemory<UInt64>((IntPtr)GameObject + 0x10);

                            UInt64 unk4 = Memory.Memory.Mem.ReadVirtualMemory<UInt64>((IntPtr)unk3 + 0x30);

                            ushort Tags = Memory.Memory.Mem.ReadVirtualMemory<ushort>((IntPtr)unk4 + 0x54);

                            if (Tags == 6)
                            {
                                UInt64 player = Memory.Memory.Mem.ReadVirtualMemory<UInt64>((IntPtr)unk4 + 0x30);



                                UInt64 player1 = Memory.Memory.Mem.ReadVirtualMemory<UInt64>((IntPtr)player + 0x18);

                                UInt64 player2 = Memory.Memory.Mem.ReadVirtualMemory<UInt64>((IntPtr)player1 + 0x28);





                                oldEntityList.Add(new Rust.Structs.Entity(player2));
                            }

                        }
                        catch
                        {

                        }

                        

                    }


                    EntityList = oldEntityList;


                    Thread.Sleep(100);

                }
            }).Start();




        }
