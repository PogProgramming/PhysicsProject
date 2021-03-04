using UnityEngine;
using UnityEngine.UI;

public class Shoot : MonoBehaviour
{
    public GameObject gun;
    Animator gunAnimator;

    public Image normalCrosshair;
    public Image hitCrosshair;

    public GameObject bullet = null;
    public GameObject orientation = null;
    public GameObject gunEndPoint = null; // To help with rotation of bullet

    public float cooldown = 0.2f;
    bool canShoot = true;

    public float gunDamage = 0;
    public float gunBulletSpeed = 0;

    public LayerMask enemyLayer;

    Camera cam = null;

    void Start()
    {
        cam = Camera.main;
        gunAnimator = gun.GetComponent<Animator>();
    }

    // Update is called once per frame
    float timer = 0;

    bool crosshairChange = false;
    float crosshairTimer = 0;
    float crosshairTimeout = 0.1f;
    void Update()
    {
        if (Input.GetMouseButton(0))
            InputShoot();

        if (timer < cooldown)
            timer += Time.deltaTime;
        else
        {
            if (!canShoot) canShoot = true;
        }

        if (crosshairChange)
        {
            crosshairTimer += Time.deltaTime;
            if(crosshairTimer > 0.1f)
            {
                crosshairTimer = 0;
                crosshairChange = false;
                CrosshairHit(false);
            }
        }
    }

    void InputShoot()
    {
        if (canShoot)
        {
            canShoot = false;
            timer = 0;
            RunGunShotAnimation();
            ShootBullet();
        }
    }
    
    void RunGunShotAnimation()
    {
        gunAnimator.Play("anim_GunShot", 0, 0f);
        //anim_GunShot
    }

    void CrosshairHit(bool _set)
    {
        if (_set)
        {
            normalCrosshair.enabled = false;
            hitCrosshair.enabled = true;

            crosshairChange = true;
        }
        else
        {
            normalCrosshair.enabled = true;
            hitCrosshair.enabled = false;
        }
    }

    void ShootBullet()
    {
        GameObject bulletObj = Instantiate(bullet, gunEndPoint.transform.position, gunEndPoint.transform.rotation);
        BulletAttack ba = bulletObj.GetComponent<BulletAttack>();
        ba.SetBullet(gunDamage, gunBulletSpeed, cam.transform.forward);

        RaycastHit hit;
        if (Physics.Raycast(gunEndPoint.transform.position, cam.transform.forward, out hit, enemyLayer))
        {
            GameObject mainEnemyBody = hit.transform.gameObject;
            bool checkGood = false;
            while (mainEnemyBody.transform.name != "EnemyPlayer" || mainEnemyBody.transform.name != "EnemyPlayer(Clone)")
            {
                if (mainEnemyBody.transform.parent == null)
                    break;

                mainEnemyBody = mainEnemyBody.transform.parent.gameObject;
                if (mainEnemyBody.transform.name == "EnemyPlayer" || mainEnemyBody.transform.name == "EnemyPlayer(Clone)")
                    checkGood = true;
            }
            if (checkGood)
            {
                CrosshairHit(true);
                mainEnemyBody.transform.GetComponent<EnemyHealth>().TakeDamage(gunDamage, hit.normal, gunBulletSpeed, hit.transform.GetComponent<Rigidbody>());
            }
        }

    }
}
