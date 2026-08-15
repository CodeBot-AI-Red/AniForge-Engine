package com.aniforge.engine

import android.app.Activity
import android.os.Bundle
import android.widget.TextView
import android.view.SurfaceView
import android.view.SurfaceHolder

class MainActivity : Activity() {
    private lateinit var surfaceView: SurfaceView
    private lateinit var statusText: TextView

    companion object {
        init {
            System.loadLibrary("aniforge")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        statusText = findViewById(R.id.status_text)
        surfaceView = findViewById(R.id.surface_view)

        val holder = surfaceView.holder
        holder.addCallback(object : SurfaceHolder.Callback {
            override fun surfaceCreated(holder: SurfaceHolder) {
                statusText.text = "AniForge Engine Inicializado"
                nativeInit()
            }

            override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
                nativeSetupGraphics(width, height)
            }

            override fun surfaceDestroyed(holder: SurfaceHolder) {
                nativeCleanup()
            }
        })
    }

    private external fun nativeInit()
    private external fun nativeSetupGraphics(width: Int, height: Int)
    private external fun nativeCleanup()
}
