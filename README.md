<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width,initial-scale=1" />
  <title>Modern Pink Calculator</title>
  <style>
    :root{
      --bg: #ffe9f1; /* soft pink page */
      --card: #fff; /* calculator face */
      --accent: #ff6fa3; /* button accent */
      --accent-2: #ff8fc0;
      --glass: rgba(255,255,255,0.7);
      --text: #222;
      --shadow: 0 10px 30px rgba(0,0,0,0.12);
      --border: 2px solid rgba(0,0,0,0.06);
      font-family: Inter, ui-sans-serif, system-ui, -apple-system, "Segoe UI", Roboto, "Helvetica Neue", Arial;
    }
    html,body{height:100%;}
    body{
      margin:0;
      background: linear-gradient(180deg,var(--bg),#fff);
      display:flex;
      align-items:center;
      justify-content:center;
      -webkit-font-smoothing:antialiased;
      -moz-osx-font-smoothing:grayscale;
    }

    /* wrapper centers the app and gives a subtle background shape */
    .page{
      width:100%;
      max-width:420px;
      margin:40px;
      display:grid;
      place-items:center;
    }

    .calculator{
      width:100%;
      background: linear-gradient(180deg, rgba(255,255,255,0.9), rgba(255,255,255,0.97));
      border-radius:20px;
      padding:18px;
      box-shadow: var(--shadow);
      border: var(--border);
      backdrop-filter: blur(6px) saturate(120%);
      overflow: hidden;
    }

    .header{
      display:flex;
      align-items:center;
      justify-content:space-between;
      gap:12px;
      margin-bottom:8px;
    }
    .brand{
      display:flex;align-items:center;gap:10px;
    }
    .logo{
      width:42px;height:42px;border-radius:10px;background:linear-gradient(135deg,var(--accent),var(--accent-2));
      display:flex;align-items:center;justify-content:center;color:#fff;font-weight:700;box-shadow:0 6px 18px rgba(255,111,149,0.18);
    }
    h1{font-size:1rem;margin:0;color:var(--text);}
    p.small{margin:0;font-size:0.8rem;color:rgba(0,0,0,0.5)}

    .screen{
      height:76px;
      background: linear-gradient(180deg, rgba(255,250,255,0.6), rgba(255,255,255,0.9));
      border-radius:12px;
      padding:12px;
      display:flex;flex-direction:column;justify-content:center;align-items:flex-end;
      font-size:1.6rem;color:var(--text);font-weight:600;
      letter-spacing:0.6px;
      margin-bottom:12px;
      border:1px solid rgba(0,0,0,0.03);
    }
    .screen .expr{font-size:0.85rem;color:rgba(0,0,0,0.45);}

    .keys{
      display:grid;grid-template-columns:repeat(4,1fr);gap:10px;
    }
    button.key{
      height:56px;border-radius:12px;border:0;font-size:1.05rem;font-weight:600;cursor:pointer;outline:none;
      box-shadow:0 6px 12px rgba(0,0,0,0.06);transition:transform .08s ease, box-shadow .08s ease;
      background:linear-gradient(180deg,#fff,#fff);
    }
    button.key:active{transform:translateY(2px);}

    button.op{background:linear-gradient(180deg,var(--accent),var(--accent-2));color:white;}
    button.ctrl{background:linear-gradient(180deg,#fafafa,#fff);}
    button.zero{grid-column:span 2;border-radius:12px;}

    .muted{color:rgba(0,0,0,0.5);font-weight:600}

    /* Responsive small screens */
    @media (max-width:420px){
      .page{padding:12px}
      .calculator{padding:14px}
    }
  </style>
</head>
<body>
  <div class="page">
    <div class="calculator" role="application" aria-label="Calculator">
      <div class="header">
        <div class="brand">
          <div class="logo">C</div>
          <div>
            <h1>PinkCalc</h1>
            <p class="small">Modern, centered & pretty</p>
          </div>
        </div>
        <div class="muted">v1.0</div>
      </div>

      <div class="screen" id="screen">
        <div class="expr" id="expr">&nbsp;</div>
        <div id="result">0</div>
      </div>

      <div class="keys">
        <button class="key ctrl" data-action="clear">C</button>
        <button class="key ctrl" data-action="back">⌫</button>
        <button class="key ctrl" data-value="%">%</button>
        <button class="key op" data-value="/">÷</button>

        <button class="key" data-value="7">7</button>
        <button class="key" data-value="8">8</button>
        <button class="key" data-value="9">9</button>
        <button class="key op" data-value="*">×</button>

        <button class="key" data-value="4">4</button>
        <button class="key" data-value="5">5</button>
        <button class="key" data-value="6">6</button>
        <button class="key op" data-value="-">−</button>

        <button class="key" data-value="1">1</button>
        <button class="key" data-value="2">2</button>
        <button class="key" data-value="3">3</button>
        <button class="key op" data-value="+">+</button>

        <button class="key zero" data-value="0">0</button>
        <button class="key" data-value=".">.</button>
        <button class="key op" data-action="equals">=</button>
      </div>
    </div>
  </div>

  <script>
    (function(){
      const screen = document.getElementById('screen');
      const exprEl = document.getElementById('expr');
      const resultEl = document.getElementById('result');
      let expression = '';

      function update(){
        exprEl.textContent = expression || '\u00A0';
        try{
          const safe = expression.replace(/[^0-9.+\-*/()%]/g, '');
          if(safe) {
            // eslint-disable-next-line no-eval
            const val = Function('return ('+safe+')')();
            resultEl.textContent = val === undefined ? '0' : String(val);
          } else resultEl.textContent = '0';
        }catch(e){ resultEl.textContent = 'Err'; }
      }

      document.querySelectorAll('button.key').forEach(btn=>{
        btn.addEventListener('click', ()=>{
          const v = btn.getAttribute('data-value');
          const action = btn.getAttribute('data-action');
          if(action==='clear'){ expression=''; update(); return; }
          if(action==='back'){ expression = expression.slice(0,-1); update(); return; }
          if(action==='equals'){ try{ const val = Function('return ('+expression.replace(/[^0-9.+\-*/()%]/g,'')+')')(); expression=String(val); update(); }catch(e){ resultEl.textContent='Err'; } return; }
          if(v){ expression += v; update(); }
        });
      });

      // keyboard support
      window.addEventListener('keydown', (e)=>{
        if((e.key>='0' && e.key<='9') || ['+','-','*','/','.','%','(',')'].includes(e.key)){
          expression += e.key; update();
        }else if(e.key==='Backspace'){ expression = expression.slice(0,-1); update(); }
        else if(e.key==='Enter'){ try{ const val = Function('return ('+expression.replace(/[^0-9.+\-*/()%]/g,'')+')')(); expression=String(val); update(); }catch(e){ resultEl.textContent='Err'; } }
        else if(e.key==='Escape'){ expression=''; update(); }
      });

      update();
    })();
  </script>
</body>
</html>
