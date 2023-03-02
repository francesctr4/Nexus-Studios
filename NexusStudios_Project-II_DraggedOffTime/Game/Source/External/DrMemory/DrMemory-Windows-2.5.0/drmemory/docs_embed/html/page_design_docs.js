[
    [ "ARM Port", "page_arm_port.html", [
      [ "ARM Port Design Document", "page_arm_port.html#autotoc_md100", [
        [ "Pattern Mode", "page_arm_port.html#autotoc_md101", [
          [ "Instrumentation to compare a memory value to an immediate", "page_arm_port.html#autotoc_md102", [
            [ "Thumb mode: can repeat single byte", "page_arm_port.html#autotoc_md103", null ],
            [ "To avoid spilling flags, try sub+cbnz in thumb mode", "page_arm_port.html#autotoc_md104", null ],
            [ "ARM mode: cannot repeat an immmed byte!  Use OP_sub x4?", "page_arm_port.html#autotoc_md105", null ],
            [ "Do 4 subtracts?", "page_arm_port.html#autotoc_md106", null ],
            [ "Switch to thumb mode just for the cmp?", "page_arm_port.html#autotoc_md107", null ],
            [ "Load immed from TLS slot", "page_arm_port.html#autotoc_md108", null ],
            [ "Go w/ unified ARM+Thumb same approach for simpler code?", "page_arm_port.html#autotoc_md109", null ],
            [ "Permanently steal another reg?", "page_arm_port.html#autotoc_md110", null ],
            [ "Put the optimizations under an option and under option switch to single-byte pattern val", "page_arm_port.html#autotoc_md111", null ],
            [ "For 2 spills, have drreg use ldm or ldrd?", "page_arm_port.html#autotoc_md112", null ]
          ] ]
        ] ]
      ] ]
    ] ]
],