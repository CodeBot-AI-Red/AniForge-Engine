package com.aniforge.engine

import android.app.Activity
import android.os.Bundle
import android.widget.TextView
import android.graphics.Color
import android.view.Gravity
import android.widget.LinearLayout

class MainActivity : Activity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val layout = LinearLayout(this).apply {
            orientation = LinearLayout.VERTICAL
            setBackgroundColor(Color.parseColor("#1a1a2e"))
            gravity = Gravity.CENTER
        }

        val title = TextView(this).apply {
            text = "AniForge Engine"
            textSize = 32f
            setTextColor(Color.parseColor("#e94560"))
            gravity = Gravity.CENTER
        }

        val subtitle = TextView(this).apply {
            text = "v1.0.0 — Inicializando..."
            textSize = 16f
            setTextColor(Color.parseColor("#ffffff"))
            gravity = Gravity.CENTER
            setPadding(0, 20, 0, 0)
        }

        val status = TextView(this).apply {
            text = "✅ Engine carregada com sucesso"
            textSize = 14f
            setTextColor(Color.parseColor("#00ff88"))
            gravity = Gravity.CENTER
            setPadding(0, 40, 0, 0)
        }

        layout.addView(title)
        layout.addView(subtitle)
        layout.addView(status)

        setContentView(layout)
    }
}
